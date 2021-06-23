#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <omp.h>
#include "Header.h"

//main function (Reyhan Fajar)
int main(){
	
	int menuchoice, error=0;

	printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
	printf("\n\n Press any key to continue! ");
	getch();

	while(error==0){
		
		//print tampilan menu awal
		system("cls");
		printf("\n                           TRAVEL MANAGEMENT SYSTEM                            ");
		printf("\n ______________________________________________________________________________\n");
		printf("\n | 1. Book Trip Baru                                                          |");
		printf("\n | 2. Tampilkan List Pesanan                                                  |");
		printf("\n | 3. Cari Pesanan                                                            |");
		printf("\n | 4. Edit Pesanan                                                            |");
		printf("\n | 5. Hapus Pesanan                                                           |");
		printf("\n | 6. Tambah Pilihan Trip                                                     |");
		printf("\n | 7. Edit Pilihan Trip                                                       |");
		printf("\n | 8. Hapus Pilihan Trip                                                      |");
		printf("\n | 9. Keluar                                                                  |");
	    printf("\n ______________________________________________________________________________\n");
	    
		do{
			//request pilihan dari user
			printf("\n Masukkan Pilihan: ");
			scanf("%d", &menuchoice);
			switch(menuchoice){
				case 1:
					error=0;
					system("cls");
					newTrip();
					break;
				case 2:
					error=0;
					system("cls");
					showUser();
					break;
				case 3:
					error=0;
					system("cls");
					searchUser();
					break;
				case 4:
					error=0;
					system("cls"); 
					editUser();
					break;
				case 5:
					error=0;
					system("cls");
					deleteUser();
					break;
				case 6:
					error=0;
					system("cls");
					Add_trip();
					break;
				case 7:
					error=0;
					system("cls");
					Edit_trip();
					break;
				case 8:
					error=0;
					system("cls");
					Delete_trip();
					break;
				case 9:
					error=0;
					printf("\n\n Program Berhenti...\n");
					exit(0);
					break;
				default:
					error=1;
					printf("\n Pilihan Invalid!\n");
					break;
				}
		}while(error==1);
	}
}



