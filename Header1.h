void calculateCost(int *total, int *tarif, int *pajak, int *penumpang);

void newTrip(){
	
	char nama[20], telp[15], email[20], date[20], trip[25];
	int penumpang, id, trip_id, price, tarif, pajak, total, max=0, error;

	
	FILE *userptr, *dataptr;
	
	userptr = fopen("user_database.txt", "a");
	dataptr = fopen("trip_database.txt", "r");
	
	printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n ______________________________________________________________________________\n");
	printf("\n  Masukkan nama pemesan : ");
	scanf(" %[^\n]s", &nama);
	printf("  Masukkan no. telepon  : ");
	scanf(" %[^\n]s", &telp);
	printf("  Masukkan email        : ");
	scanf(" %[^\n]s", &email);
	printf("  Masukkan tanggal trip : ");
	scanf(" %[^\n]s", &date);
	printf("  Jumlah penumpang      : ");
	scanf("%d", &penumpang);
	
	printf("\n\n  Pilih Trip:");
	printf("\n ______________________________________________________________________________\n");
	printf("\n  	Trip ID            Rute                  Harga/Orang\n");
	while(!feof(dataptr)){
		fscanf(dataptr, "%d", &id);
		fscanf(dataptr, "%s", trip);
		fscanf(dataptr, "%d", &price);
		max++;
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
	calculateCost(&total, &price, &pajak, &penumpang);	
	
	fprintf(userptr, "%s, %s, %s, %s, %d, %d\n", nama, telp, email, date, trip_id, total);
	fclose(userptr);
	fclose(dataptr);
	
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
	printf("\n Press Any Key to Continue!");
	getch();
}

void showUser(){
	//char nama[20], telp[15], email[20], date[20];
	//int count=0, trip_id, total;
	char read[150];
	FILE *userptr;

	printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n\n ------------------------------------------------------------------------------\n");		
	
	if ((userptr = fopen("user_database.txt","r")) == NULL){
    	printf("\n Error: File not found!\n");
	}

  	// baca isi file dengan gets lalu simpan ke read
  	else{
  		
		printf("                                  LIST PESANAN");
		printf("\n ------------------------------------------------------------------------------");
		
		
		while(fgets(read, 150, userptr)!=NULL){
			
			/*
			fscanf(userptr, "%20[^,]s", nama);
			fscanf(userptr, "%15[^,]s", telp);
			fscanf(userptr, "%20[^,]s", email);
			fscanf(userptr, "%20[^,]s", date);
			fscanf(userptr, "%2[^,]d", &trip_id);
			fscanf(userptr, "%d", &total);
			
			//fscanf(userptr, "%20[^,]s, %15[^,]s, %20[^,]s, %20[^,]s, %2[^,]d, %d", nama, telp, email, date, &trip_id, &total);
			
			count++;
			printf("\n  %d.", count);
			printf("\n  Nama pemesan     : %s", nama);
			printf("\n  Nomor telepon    : %s", telp);
			printf("\n  Email            : %s", email);
			printf("\n  Tanggal trip     : %s", date);
			printf("\n  Trip ID          : %d", trip_id);
			printf("\n  Total biaya      : Rp. %d", total);
			*/
			
			printf("\n %s", read);
			printf("\n ------------------------------------------------------------------------------\n");
		}
	}
	
  	// tampilkan isi file	
	fclose(userptr);
	printf("\n\n Press Any Key to Continue!");
	getch();
}

void searchUser(){
    char word[1000];
    char search[25];
    char name[50] = {0};
    
    printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n ______________________________________________________________________________\n");

    while(name[0] != '0'){
        FILE *userptr = fopen("user_database.txt", "r");
        
            if (userptr == NULL)
                printf("\n Error: File not found!\n");
    
            printf("\n Masukkan nama yang ingin anda cari (Masukkan '0' untuk berhenti): ");
            scanf("%s", name);
	        while(fscanf(userptr,"%s", search) == 1){
	        	if(strcmpi(search, name)==0){           	
	            	fgets(word, 150, userptr);
					printf("\n %s%s", search, word);
					printf("\n ------------------------------------------------------------------------------\n");
	               }
	           }
	        if(!feof(userptr))
				printf("\n Data Tidak Ditemukan!\n");
            fclose(userptr);
    }
}

void editUser(){
	
	char search[25], name[25], buffer[150];
	int line=1, count=0, c;
	char nama[20], telp[15], email[20], date[20], trip[25];
	int penumpang, id, trip_id, price, tarif, pajak, total, max=0, error;
	FILE *userptr = fopen("user_database.txt", "r");
	
	printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n ______________________________________________________________________________\n");
	
	if(userptr == NULL)
		printf("\n Error: File not found!\n");
	
	else{
		printf("\n Masukkan Nama Pemesan Yang Ingin Anda Edit: ");
		scanf("%s", search);

		while(fscanf(userptr,"%s", name) == 1){
			
			c=fgetc(userptr);
			if(c=='\n')
				++line;
					
			if(strcmpi(search, name)==0){	
					
				FILE *dataptr = fopen("trip_database.txt", "r");
				FILE *tempptr = fopen("temp.txt", "w");
				
				printf("\n Data Ditemukan!");
				printf("\n\n ------------------------------------------------------------------------------\n");
				printf("                                 EDIT DATA");
				printf("\n ------------------------------------------------------------------------------");
					
				printf("\n  Masukkan nama pemesan : ");
				scanf(" %[^\n]s", &nama);
				printf("  Masukkan no. telepon  : ");
				scanf(" %[^\n]s", &telp);
				printf("  Masukkan email        : ");
				scanf(" %[^\n]s", &email);
				printf("  Masukkan tanggal trip : ");
				scanf(" %[^\n]s", &date);
				printf("  Jumlah penumpang      : ");
				scanf("%d", &penumpang);
				
				printf("\n\n  Pilih Trip:");
				printf("\n ______________________________________________________________________________\n");
				printf("\n  	Trip ID            Rute                  Harga/Orang\n");
				while(!feof(dataptr)){
					fscanf(dataptr, "%d", &id);
					fscanf(dataptr, "%s", trip);
					fscanf(dataptr, "%d", &price);
					max++;
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
				calculateCost(&total, &price, &pajak, &penumpang);
				
				fflush(userptr);
				rewind(userptr);
				
				while(fgets(buffer, 150, userptr)!=NULL){
					count++;
					
					if(count==line)
						fprintf(tempptr, "%s, %s, %s, %s, %d, %d\n", nama, telp, email, date, trip_id, total);
					else
						fputs(buffer, tempptr);
				}
					
				fclose(userptr);
				fclose(dataptr);
				fclose(tempptr);
				
				remove("user_database.txt");
				rename("temp.txt", "user_database.txt");
				
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
			}
		}
		if(feof(userptr))
			printf("\n Data Tidak Ditemukan!\n");
	}
	
	printf("\n Press Any Key to Continue!");
	getch();
}

void deleteUser(){
	
	char search[25], name[25], word[50], buffer[150];
	int confirm, line=1, count=0, c;
	FILE *userptr = fopen("user_database.txt", "r");
	
	printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n ______________________________________________________________________________\n");
	
	if(userptr == NULL){
		printf("\n Error: File not found!\n");
	}
	
	else{
		printf("\n Masukkan Nama Pemesan Yang Ingin Anda Hapus: ");
		scanf("%s", search);

		while(fscanf(userptr,"%s", name) == 1){
			
			c=fgetc(userptr);
			if(c=='\n')
				++line;
					
			if(strcmpi(search, name)==0){	
			 	fscanf(userptr, "%[^,]s", word);			
				printf("\n\n Hapus Data Dari (%s %s)? 0=Tidak, 1=Iya: ", name, word);
				scanf("%d", &confirm);
				
				if(confirm==0)
				printf("\n Hapus Data Dibatalkan!\n");
				
				else if(confirm==1){
					
					FILE *tempptr = fopen("temp.txt", "w");

					rewind(userptr);
					
					while(fgets(buffer, 150, userptr)!=NULL){
						count++;
			
						if(count!=line)
							fputs(buffer, tempptr);
						else
							continue;	
					}
					
					fclose(userptr);
					fclose(tempptr);
					
					remove("user_database.txt");
					rename("temp.txt", "user_database.txt");
					printf("\n Data Berhasil Dihapus!\n");
				}
			}
		}
		if(feof(userptr))
			printf("\n Data Tidak Ditemukan!\n");
	}
	
	printf("\n Press Any Key to Continue!");
	getch();
}

void calculateCost(int *total, int *tarif, int *pajak, int *penumpang){
	
	*total = *tarif * *penumpang;
	*pajak = *total/10;
	*total = *pajak + *total;
}
