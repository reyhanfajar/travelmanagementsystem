//struct node dari pilihan trip (Muhammad Fadel Akbar)
typedef struct trip_database{
	int trip_id;
	char destination[50];
	int cost;
	struct trip_database *link;
}TRIP;


//function menghitung jumlah total tagihan (Imam Azka)
void calculateCost(int *total, int *tarif, int *pajak, int *penumpang){
	*total = *tarif * *penumpang;
	*pajak = *total/10;
	*total = *pajak + *total;
}


//function read file menjadi linked list (Muhammad Fadel Akbar)
void Read(TRIP *head){
	
	FILE *fptr; 
	fptr = fopen("trip_database.txt", "r"); //file handling membaca trip_database.txt
	int counter = 0, i = 1, flag = 0, c;
	
	//jika file tidak ada maka akan dibuatkan filenya
	if(fptr == NULL){
		fclose(fptr);
		fopen("trip_database.txt", "w");
		fclose(fptr);
	}
	
	else{
		//menghitung jumlah baris/line di trip_database.txt
		while(!feof(fptr)){
			c = fgetc(fptr);
			if(c == '\n'){
				counter++;
			}
		}
		rewind(fptr); //rewind supaya pointer mengarah ke awal karakter di file txt
		
		while(i<=counter){
		
			//membuat head
			if(flag == 0){
				//buat head berdasarkan line pertama file
				fscanf(fptr, "%d", &head->trip_id);
				fscanf(fptr, "%s", head->destination);
				fscanf(fptr, "%d", &head->cost);
				head->link = NULL;
				flag = 1;
				i++;
			}
			
			//membuat node" selanjutnya	
			else{
				
				TRIP *ptr;
				TRIP *temp;
				ptr = head;
				temp = (TRIP*)malloc(sizeof(TRIP));
		
				fscanf(fptr, "%d", &temp->trip_id);
				fscanf(fptr, "%s", temp->destination);
				fscanf(fptr, "%d", &temp->cost);
				temp->link = NULL;
				//node maju
				while(ptr->link != NULL){
					ptr = ptr->link;
				}
				ptr->link = temp;
				i++; 
			}
		}
	fclose(fptr);
	}
}


//function menambah pesanan user baru(Imam Azka)
void newTrip(){
	
	char nama[50], telp[20], email[25], date[25], trip[50];
	int penumpang, id, trip_id, price, tarif, pajak, total, max=0, error, c, i;

	FILE *userptr, *dataptr;
	
	userptr = fopen("user_database.txt", "a");	//file database user
	dataptr = fopen("trip_database.txt", "r");	//file database pilihan trip
	
	//perhitungan banyak data dari database trip
	while(!feof(dataptr)){
  		c=getc(dataptr);
  		if(c == '\n')
  			max++;
	}

	printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n ______________________________________________________________________________\n");
	printf("                                    INPUT DATA");
	printf("\n ------------------------------------------------------------------------------");
	//request input data baru dari user
	printf("\n  Masukkan nama pemesan : ");
	scanf(" %50[^\n]s", &nama);
	printf("  Masukkan no. telepon  : ");
	scanf(" %20[^\n]s", &telp);
	printf("  Masukkan email        : ");
	scanf(" %25[^\n]s", &email);
	printf("  Masukkan tanggal trip : ");
	scanf(" %25[^\n]s", &date);
	printf("  Jumlah penumpang      : ");
	scanf("%d", &penumpang);

	rewind(dataptr);
	//proses pemilihan trip id sesuai keinginan user
	printf("\n\n  Pilih Trip:");
	printf("\n ______________________________________________________________________________\n");
	printf("\n  	Trip ID            Rute                  Harga/Orang\n");

	for(i=0; i<max; i++){
		fscanf(dataptr, "%d", &id);
		fscanf(dataptr, "%s", trip);
		fscanf(dataptr, "%d", &price);
		printf(" 	   %d		%s		Rp. %d\n", id, trip, price);
	}

	printf("\n ______________________________________________________________________________\n");
	do{
		printf("\n Pilih trip id: ");
		scanf("%d", &trip_id);
		
		if(trip_id<1 || trip_id>max){
			error=1;
			printf("\n Pilihan Invalid!\n");
		}
		else
			error=0;
	}while(error==1);
	
	rewind(dataptr);

	for(i=0; i<max; i++){
		fscanf(dataptr, "%d", &id);
		fscanf(dataptr, "%s", trip);
		fscanf(dataptr, "%d", &price);
		
		if(trip_id==id)
			i=max;
	}
	calculateCost(&total, &price, &pajak, &penumpang);//perhitungan total biaya	
	
	//menaruh data baru ke file database user
	fprintf(userptr, "%s , %s, %s, %s, %d, %d\n", nama, telp, email, date, trip_id, total);
	fclose(userptr);
	fclose(dataptr);
	
	//print hasil data baru
	system("cls");
	printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n\n ------------------------------------------------------------------------------\n");
	printf("                                 DETAIL PESANAN");
	printf("\n ------------------------------------------------------------------------------");
	printf("\n  Nama pemesan     : %s", nama);
	printf("\n  Nomor telepon    : %s", telp);
	printf("\n  Email            : %s", email);
	printf("\n  Tanggal trip     : %s", date);
	printf("\n  Jumlah penumpang : %d", penumpang);
	printf("\n  Pilihan trip     : %s", trip);
	printf("\n  Jumlah tarif     : Rp. %d", price*penumpang);
	printf("\n  Pajak 10%%        : Rp. %d", pajak);
	printf("\n  Total biaya      : Rp. %d", total);
	printf("\n ------------------------------------------------------------------------------\n");
	
	printf("\n Data Tersimpan!\n");
	printf("\n Press Any Key to Continue! ");
	getch();
}


//fungsi untuk menampilkan pemesan(Reyhan Fajar)
void showUser(){	
	
	char nama[100], telp[100], email[100], date[100];
	int count=0, trip_id, total, c, i=0, line=0;
	FILE *userptr;

	printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n\n ------------------------------------------------------------------------------\n");	
		
	//membuka user_database.txt dengan status "r" dan mengaliaskannya dengan userptr
	if ((userptr = fopen("user_database.txt","r")) == NULL){	
    	printf("\n Error: File not found!\n");	//file tidak ditemukan
	}
	// bila file ada
  	else{
  		//menghitung jumlah line
  		while(!feof(userptr)){	//bila pembacaan belum di akhir
  			c=getc(userptr);	//mengambil character dari userptr
  			if(c == '\n')
  				line++;
		  }
  		
		printf("                                  LIST PESANAN");
		printf("\n ------------------------------------------------------------------------------");
		
		rewind(userptr);	//mengembalikan pembacaan ke awal file user_database.txt

		for(i=0; i<line; i++){
			
			fscanf(userptr, "%[^,]%s", nama);
			fscanf(userptr, " %[^,]%s", telp);
			fscanf(userptr, " %[^,]%s", email);
			fscanf(userptr, " %[^,]%s", date);
			fscanf(userptr, "%d", &trip_id);
			fscanf(userptr, ",%d", &total);
			
			c=getc(userptr);	//mengambil character dari userptr	
			count++;
			
			printf("\n  %d.", count);
			printf("\n  Nama pemesan     : %s", nama);
			printf("\n  Nomor telepon    : %s", telp);
			printf("\n  Email            : %s", email);
			printf("\n  Tanggal trip     : %s", date);
			printf("\n  Trip ID          : %d", trip_id);
			printf("\n  Total biaya      : Rp. %d\n", total);

			printf("\n ------------------------------------------------------------------------------");
		}
	}

	fclose(userptr);	//menutup userptr
	printf("\n\n Press Any Key to Continue! ");
	getch();	//kembali ke menu awal
}


//fungsi untuk mencari pemesan(Reyhan Fajar)
void searchUser(){	
	
	char nama[100], telp[100], email[100], date[100];
	int count=0, trip_id, total, c, i=0, line=0;
    char search[25];
    char name[50] = {0};
    
    FILE *userptr;	
    
    if (userptr == NULL)	
    	printf("\n Error: File not found!\n");	//bila file tidak ada
    //bila ada, maka membuka user_database.txt dengan status "r" dan mengaliaskannya dengan userptr
	userptr = fopen("user_database.txt", "r");
	//menghitung jumlah line
    while(!feof(userptr)){	//bila pembacaan belum di akhir
  		c=getc(userptr);	//mengambil character dari userptr
  		if(c == '\n')
  			line++;
	}
	fclose(userptr);	//menutup userptr
    
    printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n ______________________________________________________________________________\n");
	

    while(name[0] != '0'){	//selama user tidak menginput 0 pada search, maka program akan meminta 
        
   	    printf("\n\n Masukkan nama yang ingin anda cari (Masukkan '0' untuk berhenti): ");
	    scanf("%s", name);
	    userptr = fopen("user_database.txt", "r");	//membuka user_database.txt dengan status "r" dan mengaliaskannya dengan userptr
	    system("cls");	//membersihkan layar cmd
		printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
		printf("\n ______________________________________________________________________________\n");
		printf("\n\n ------------------------------------------------------------------------------\n");
		printf("                                DETAIL PESANAN");
	    	    
	    rewind(userptr);	//mengembalikan pembacaan dari awal userptr

	    for(i=0; i<line; i++){
			
			fscanf(userptr,"%s", search);
			fscanf(userptr, "%[^,]%s", nama);
			fscanf(userptr, " %[^,]%s", telp);
			fscanf(userptr, " %[^,]%s", email);
			fscanf(userptr, " %[^,]%s", date);
			fscanf(userptr, "%d", &trip_id);
			fscanf(userptr, ",%d", &total);
			
			if(strcmpi(search, name)==0 || strcmpi(nama, name)==0){	//bila search sesuai dengan pemesan
				c=getc(userptr);	//mengambil character dari userptr
				//menampilkan data pemesan yang sesuai dengan search
				printf("\n ------------------------------------------------------------------------------");
				printf("\n  Nama pemesan     : %s%s", search, nama);
				printf("\n  Nomor telepon    : %s", telp);
				printf("\n  Email            : %s", email);
				printf("\n  Tanggal trip     : %s", date);
				printf("\n  Trip ID          : %d", trip_id);
				printf("\n  Total biaya      : Rp. %d\n", total);
				printf("\n ------------------------------------------------------------------------------");
				
				}
			
			}
			fclose(userptr);	//menutup userptr
    }
}


//function meng-edit isi dari user(Imam Azka)
void editUser(){
	
	char search[25], name[25], buffer[150];
	int line=1, count=0, c, i;
	char nama[50], telp[20], email[25], date[25], trip[50];
	int penumpang, id, trip_id, price, tarif, pajak, total, max=0, error;
	
	FILE *userptr = fopen("user_database.txt", "r");	//file database user
	FILE *dataptr = fopen("trip_database.txt", "r");	//file database trip
	
	printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n ______________________________________________________________________________\n");
	
	//jika file tidak ada
	if(userptr==NULL || dataptr==NULL)
		printf("\n Error: File not found!\n");
	
	else{
		//perhitungan banyak data dari database trip
		while(!feof(dataptr)){
	  		c=getc(dataptr);
	  		if(c == '\n')
	  			max++;
		}
		rewind(dataptr);
		
		printf("\n Masukkan nama pemesan yang ingin anda edit: ");
		scanf("%s", search);
		
		fclose(userptr);
		userptr = fopen("user_database.txt", "r");
		
		//proses pencarian data
		while(fscanf(userptr,"%s", name) == 1){
			
			c=fgetc(userptr);
			if(c=='\n')
				++line;
			
			//jika data ditemukan maka akan request data baru (sama seperti menambah user baru)		
			if(strcmpi(search, name)==0){	
					
				FILE *tempptr = fopen("temp.txt", "w");
				
				printf("\n Data Ditemukan!");
				printf("\n\n ------------------------------------------------------------------------------\n");
				printf("                                 EDIT DATA");
				printf("\n ------------------------------------------------------------------------------");
					
				printf("\n  Masukkan nama pemesan : ");
				scanf(" %50[^\n]s", &nama);
				printf("  Masukkan no. telepon  : ");
				scanf(" %20[^\n]s", &telp);
				printf("  Masukkan email        : ");
				scanf(" %25[^\n]s", &email);
				printf("  Masukkan tanggal trip : ");
				scanf(" %25[^\n]s", &date);
				printf("  Jumlah penumpang      : ");
				scanf("%d", &penumpang);
				
				printf("\n\n  Pilih Trip:");
				printf("\n ______________________________________________________________________________\n");
				printf("\n  	Trip ID            Rute                  Harga/Orang\n");
				
				for(i=0; i<max; i++){
					fscanf(dataptr, "%d", &id);
					fscanf(dataptr, "%s", trip);
					fscanf(dataptr, "%d", &price);
					printf(" 	   %d		%s		Rp. %d\n", id, trip, price);
				}
				
				printf("\n ______________________________________________________________________________\n");
				do{
					printf("\n Pilih trip id: ");
					scanf("%d", &trip_id);
					
					if(trip_id<1 || trip_id>max){
						error=1;
						printf("\n Pilihan Invalid!\n");
					}
					else
						error=0;
				}while(error==1);
				
				rewind(dataptr);
				while(!feof(dataptr)){
					fscanf(dataptr, "%d", &id);
					fscanf(dataptr, "%s", trip);
					fscanf(dataptr, "%d", &price);
					
					if(trip_id==id){
						break;
					}
				}
				calculateCost(&total, &price, &pajak, &penumpang);//perhitungan pajak
				
				fflush(userptr);
				rewind(userptr);
				
				//proses duplikasi isi file ke temp.txt, kemudian temp.txt menjadi database user yg baru
				while(fgets(buffer, 150, userptr)!=NULL){
					count++;
					
					if(count==line)
						fprintf(tempptr, "%s , %s, %s, %s, %d, %d\n", nama, telp, email, date, trip_id, total);
					else
						fputs(buffer, tempptr);
				}
			
				fclose(userptr);
				fclose(dataptr);
				fclose(tempptr);
				
				system("cls");
				printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
				printf("\n\n ------------------------------------------------------------------------------\n");
				printf("                                 TRIP DETAILS");
				printf("\n ------------------------------------------------------------------------------");
				printf("\n  Nama pemesan     : %s", nama);
				printf("\n  Nomor telepon    : %s", telp);
				printf("\n  Email            : %s", email);
				printf("\n  Tanggal trip     : %s", date);
				printf("\n  Jumlah penumpang : %d", penumpang);
				printf("\n  Pilihan trip     : %s", trip);
				printf("\n  Jumlah tarif     : Rp. %d", price*penumpang);
				printf("\n  Pajak 10%%        : Rp. %d", pajak);
				printf("\n  Total biaya      : Rp. %d", total);
				printf("\n ------------------------------------------------------------------------------\n");
				printf("\n Data Tersimpan!\n");
				
				//swap temp dengan user database
				remove("user_database.txt");
				rename("temp.txt", "user_database.txt");
				break;
			}
		}
		//jika data tidak ditemukan
		if(feof(userptr))
			printf("\n Data Tidak Ditemukan!\n");
	}
	
	printf("\n Press Any Key to Continue! ");
	getch();
}


//function menghapus data dari user(Imam Azka)
void deleteUser(){
	
	char search[25], name[25], word[50], buffer[150];
	int confirm, line=1, count=0, c, error=0;
	FILE *userptr = fopen("user_database.txt", "r");//read file database user
	
	printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n ______________________________________________________________________________\n");
	
	//jika file tidak ditemukan
	if(userptr == NULL){
		printf("\n Error: File not found!\n");
	}
	
	else{
		printf("\n Masukkan nama pemesan yang ingin anda hapus: ");
		scanf("%s", search);
		
		fclose(userptr);
		userptr = fopen("user_database.txt", "r");
		
		//proses pencarian
		while(fscanf(userptr,"%s", name) == 1){
			
			c=fgetc(userptr);
			if(c=='\n')
				++line;
					
			if(strcmpi(search, name)==0){	
			 	fscanf(userptr, "%[^,]s", word);
				
				do{			
					printf("\n Hapus Data Dari %s %s? 0 = Tidak, 1 = Iya : ", name, word);
					scanf("%d", &confirm);
					
					system("cls");
					printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
					printf("\n ______________________________________________________________________________\n");
						
					if(confirm==0){
						error = 0;
						printf("\n Hapus Data Dibatalkan!\n");
					}
						
					else if(confirm==1){
						error = 0;
						FILE *tempptr = fopen("temp.txt", "w");
						rewind(userptr);
						
						//proses duplikasi file ke temp.txt, kemudian temp.txt menjadi database user yang baru	
						while(fgets(buffer, 150, userptr)!=NULL){
							count++;
					
							if(count!=line)
								fputs(buffer, tempptr);
							else
								continue;	
						}
							
						fclose(userptr);
						fclose(tempptr);
						//swap temp dengan user_database
						remove("user_database.txt");
						rename("temp.txt", "user_database.txt");
							
						printf("\n Data Berhasil Dihapus!\n");
					}
					
					else{
						error = 1;
						printf("\n Invalid Input!\n");
					}
						
				}while(error==1);
				break;
			}
		}
		//jika data tidak ditemukan
		if(feof(userptr))
			printf("\n Data Tidak Ditemukan!\n");
		fclose(userptr);
	}
	
	printf("\n Press Any Key to Continue! ");
	getch();
}


//function menambah pilihan trip baru (Muhammad Fadel Akbar)
void Add_trip(){
	
	int harga;
	char city[50];
	
	TRIP *head, *ptr, *newtrip;

	head = (TRIP*)malloc(sizeof(TRIP));
	newtrip = malloc(sizeof(TRIP));
	Read(head);
	
	//Berusaha menambahkan data ke baris terakhir file.txt
	FILE *fptr = fopen("trip_database.txt", "a");
	
	printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n ______________________________________________________________________________\n");
	printf("                                    TRIP BARU");
	printf("\n ------------------------------------------------------------------------------");

	printf("\n  Masukkan nama trip : ");
	scanf("%s", city);
	printf("\n  Masukkan harga trip : ");
	scanf("%d", &harga);
	
	//Trip id selanjutnya urut secara ascending dari sebelumnya
	ptr = head;
	while(ptr->link != NULL){
		ptr = ptr->link;
	}
	newtrip->trip_id = ptr->trip_id+1; //supaya urut +1 dari sebelumnya
	sprintf(newtrip->destination, city);
	newtrip->cost = harga;
	newtrip->link = NULL;

	//Write ke file.txt
	ptr->link = newtrip;
	fprintf(fptr, "%d %s %d\n", newtrip->trip_id, newtrip->destination, newtrip->cost);
	fclose(fptr);
	
	printf("\n  Data Tersimpan!\n");
	printf("\n  Press Any Key to Continue! ");
	getch();
}


//function meng-edit isi pilihan trip (Muhammad Fadel Akbar)
void Edit_trip(){
	
	int id, harga, error;
	char city[50];
	
	TRIP *head = (TRIP*)malloc(sizeof(TRIP));
	Read(head);
	FILE *fptr = fopen("trip_database.txt", "w");
	TRIP *ptr;
	
	printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n ______________________________________________________________________________\n");
	printf("                                     EDIT TRIP");
	printf("\n ------------------------------------------------------------------------------");
	printf("\n  	Trip ID            Rute                  Harga/Orang\n");
	
	ptr=head;
	//Menampilkan isi file.txt
	while(ptr!=NULL){
		printf(" 	   %d		%s		Rp. %d\n", ptr->trip_id, ptr->destination, ptr->cost);
		ptr = ptr->link;
	}

	do{
		//Pencarian berdasarkan trip id
		error = 0;
		ptr = head;
		printf("\n  Masukkan trip id yang ingin dihapus: ");
		scanf("%d", &id);
		
		while(ptr->trip_id != id){
			
			ptr = ptr->link;
			//Jika sudah membaca sampai node terakhir dan id-nya tidak ada yang sama
			//maka akan meminta input kembali (break)
			if(ptr->link == NULL && ptr->trip_id != id){
				printf("\n  Data Tidak Ditemukan!\n");
				error = 1;
				break;
			}
		}
	}while(error == 1);
	
	//Meminta input user untuk mengubah data trip
	printf("\n  	Trip ID            Rute                  Harga/Orang\n");
	printf(" 	   %d		%s		Rp. %d\n", ptr->trip_id, ptr->destination, ptr->cost);
	printf("\n  Ganti nama trip (%d) menjadi : ", ptr->trip_id);
	scanf("%s", city);
	printf("\n  Ganti harga trip menjadi : ");
	scanf("%d", &harga);
	sprintf(ptr->destination, city);
	ptr->cost = harga;
	
	system("cls");
	printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n ______________________________________________________________________________\n");
	printf("                                     LIST TRIP");
	printf("\n ------------------------------------------------------------------------------");
	printf("\n  	Trip ID            Rute                  Harga/Orang\n");
	
	//Menulis ulang dari awal isi node ke file.txt
	ptr = head;
	while(ptr!= NULL){
		fprintf(fptr, "%d %s %d\n", ptr->trip_id, ptr->destination, ptr->cost);
		printf(" 	   %d		%s		Rp. %d\n", ptr->trip_id, ptr->destination, ptr->cost);
		ptr = ptr->link;
	}
	
	fclose(fptr);
	
	printf("\n  Data Tersimpan!\n");
	printf("\n  Press Any Key to Continue! ");
	getch();
}


//function menghapus pilihan trip (Muhammad Fadel Akbar)
void Delete_trip(){
	
	TRIP *p;
	TRIP *head = (TRIP*)malloc(sizeof(TRIP));
	FILE *fptr;
	//Menampilkan isi dari file.txt
	Read(head);
	
	int error = 0, id, i, flag = 0, count = 0, c, data;
	TRIP *ptr = head;
	TRIP *ptr2 = head;
	//Berusaha write dan read file
	fptr = fopen("trip_database.txt", "r+");
	
	//Menghitung jumlah baris
	while(!feof(fptr)){
		c = fgetc(fptr);
		if(c == '\n'){
			count++;
		}
	}
	rewind(fptr); //Kembali ke baris awal file.txt
	fclose(fptr); //Menutup file.txt
	fptr = fopen("trip_database.txt", "w"); //Membuka ulang file dalam mode write
	
	printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n ______________________________________________________________________________\n");
	printf("                                     HAPUS TRIP");
	printf("\n ------------------------------------------------------------------------------");
	
	printf("\n\n  Pilihan Trip: ");
	printf("\n ______________________________________________________________________________\n");
	printf("\n  	Trip ID            Rute                  Harga/Orang\n");
	
	p=head;
	//Menampilkan isi file.txt
	while(p!=NULL){
		printf(" 	   %d		%s		Rp. %d\n", p->trip_id, p->destination, p->cost);
		p = p->link;
	}
	
	do{
		ptr = head;
		error = 0;
		flag = 0;
		printf("\n  Masukkan trip id yang ingin anda hapus: ");
		scanf("%d", &id);
		data=id;
		//Akan memeinta input lagi jika id kurang dari nol dan id lebih besar dari jumlah baris di file.txt
		if(id <= 0 || id > count){
			printf("\n  Error: Invalid input!\n");
			error = 1;
			flag = 1;
		}
		
		//Khusus menghapus data di baris pertama file.txt
		if(id == 1 && flag != 1){
			head = ptr->link;
			free(ptr);
			ptr = NULL;
			p = head;
			
			while(p != NULL){
				p->trip_id--;
				fprintf(fptr, "%d %s %d\n", p->trip_id, p->destination, p->cost);
				p = p->link;
			}
			
			printf("\n  Data Terhapus!\n");
		}
		
		//Menghapus data di baris2 berikutnya file.txt
		else if(id != 1 && flag != 1){
			while(id != 1){
				ptr2 = ptr;
				ptr = ptr->link;
				id--;
			}
			
			ptr2->link = ptr->link;
			free(ptr);
			ptr = NULL;
			printf("\n  Data Terhapus!\n");
			ptr = head;
			
			//Menulis ulang ke file.txt dimana ada trip yang sudah dihapus
			while(ptr != NULL){
				if(ptr->trip_id != 1 && data!=count)
					ptr->trip_id--;
				fprintf(fptr, "%d %s %d\n", ptr->trip_id, ptr->destination, ptr->cost);
				ptr = ptr->link;
			}	
		}	
	}while(error == 1);
	
	fclose(fptr);
	
	printf("\n  Press Any Key to Continue! ");
	getch();
}
