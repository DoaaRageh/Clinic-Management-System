#include <stdio.h>
#include <stdlib.h>
#include "STD_Types.h"
#include "Project.h"

void AddPatient(St_Patient **head, u32 id, u8 *name, u32 age, u8 gender);
void PrintPatientRecord(St_Patient **head, u32 id);
void EditPatientRecord(St_Patient **head, u32 id, u8 *name, u32 age, u8 gender);
void PrintReservations(St_Reservation **head);
void PrintAvailableReservations(St_Reservation **head);
void ReserveSlot(St_Reservation **head, u32 id, f32 slot);
void CancelReservation(St_Reservation **head, u32 id);
u16 CheckID(St_Patient **head, u32 id);
u16 CheckReservation(St_Reservation **head, u32 id);
void CreateSlots(St_Reservation **head);

void main(){
	
	u16 user_choice, admin_choice, n;
	St_Patient *h=NULL;
	St_Reservation *s=NULL;
	f32 slot;
	u8 name[15], gender, mode;
	u32 p_id, age, pass;
	
	/*declaring flag to exit from the system 
	after entering wrong password for 3 times*/
	int flag=2;
	
	/*calling function to create timeslots list*/
	CreateSlots(&s);
	
	while(1){
		printf("\nEnter A to enter admin mode\nEnter U to enter user mode\nEnter E to exit the system\n");
		scanf(" %c",&mode);
		
		/*if the user enter E close the system*/
		if(mode == 'e' || mode == 'E'){
			break;
		}
		
		switch(mode){
				/*in admin mode*/
				case 'A':
				case 'a':
					printf("\nPlease enter the password: ");
					scanf("%d",&pass);
					
					/*loop to allow the admin to try only 3 times for the password*/
					for(int i=0;i<3;i++){
						if(pass==1234){
							printf("\n  ***** WELCOME *****\n");
							flag=1;
							
							while(1){
								printf("\nEnter 1 to Add new patient\nEnter 2 to Edit patient record\nEnter 3 to Reserve a slot with the doctor\nEnter 4 to Cancel reservation\nEnter 5 to exit\n");
								scanf("%d",&admin_choice);
								
								/*exit from the loop if the admin enter 5*/
								if(admin_choice==5){
									flag=2;
									break;
								}
								
								switch(admin_choice){
									/*Add new patient record*/
									case 1:
										printf("\nEnter the ID: ");
										scanf("%d",&p_id);
										
										/*if the id is already exist make the admin choose another id*/
										if(CheckID(&h,p_id)==1){
											while(CheckID(&h,p_id)==1){
												printf("This ID is already exist, Please enter another ID: ");
												scanf("%d",&p_id);
											}
										}
										
										printf("Enter the Name: ");
										scanf("%s",&name);
										printf("Enter the Age: ");
										scanf("%d",&age);
										printf("Enter the Gender(F/M): ");
										scanf(" %c",&gender);
										AddPatient(&h, p_id, name, age, gender);
										printf("\nPatient added successfully.\n");
										break;
										
									/*Edit patient record*/	
									case 2:
										printf("\nEnter the patient ID you want to edit: ");
										scanf("%d",&p_id);
										
										/*if the id is not exist display error message and exit from the case*/
										if(CheckID(&h,p_id)==0){
											printf("\nThis ID is not exist\n");
											break;
										}
										
										printf("Enter the Name: ");
										scanf("%s",&name);
										printf("Enter the Age: ");
										scanf("%d",&age);
										printf("Enter the Gender(F/M): ");
										scanf(" %c",&gender);
										EditPatientRecord(&h,p_id,name,age,gender);
										printf("\nPatient modified successfully.\n");
										break;
										
									/*Reserve a slot with the doctor*/
									case 3:
										printf("\nThe available slots:\n");
										PrintAvailableReservations(&s);
										printf("\n\nEnter the patient ID: ");
										scanf("%d",&p_id);
										
										/*if the id is not exist display error message and exit from the case*/
										if(CheckID(&h,p_id)==0){
											printf("\nThis ID is not exist\n");
											break;
										}
										
										/*Check if the patient already has a reservation*/
										if(CheckReservation(&s,p_id)==1){
											printf("This patient already has a reservation\n");
											printf("\nEnter 1 if you want to cancel old reservation and make new reservation\nEnter 2 to cancel operation\n");
											scanf("%d",&n);
											
											/*Change the old reservation if the patient wants to change it*/
											if(n==1){
												CancelReservation(&s,p_id);
											}
											
											/*Cancel the operation if the patient does not want to change the old reservation*/
											else{
												break;
											}
										}
										
										printf("Enter the time you want: ");
										scanf("%f",&slot);
										ReserveSlot(&s,p_id,slot);
										printf("\nSuccessfully reservation.\n");
										break;
									
									/*Cancel reservation*/
									case 4:
										printf("\nEnter patient ID whose reservation you want to cancel: ");
										scanf("%d",&p_id);
										
										/*if the id is not exist display error message and exit from the case*/
										if(CheckID(&h,p_id)==0){
											printf("\nThis ID is not exist\n");
											break;
										}
										
										CancelReservation(&s,p_id);
										printf("\nReservation has been canceled successfully.\n");
										break;	
										
									default:
										printf("\nInvalid Option\n");
										break;
								}
							}
							break;
						}
						
						else{
							if(i<2){
								printf("Try Again: ");
								scanf("%d",&pass);
							}
							else if(i==2){
								flag=0;
								printf("\nIncorrect password for 3 times, No more tries.\n");
							}	
						}
					}
					break;
				/*in user mode*/
				case 'U':
				case 'u':

					while(1){
						printf("\nEnter 1 to view patient record\nEnter 2 to view today's reservations\nEnter 3 to exit\n");
						scanf("%d",&user_choice);
						
						/*exit from the loop if the user enter 3*/
						if(user_choice==3){
							break;
						}
						
						switch(user_choice){
							/*View patient record*/
							case 1:
								printf("\nEnter the patient ID you want to view: ");
								scanf("%d",&p_id);
								
								/*if the id is not exist display error message and exit from the case*/
								if(CheckID(&h,p_id)==0){
									printf("\nThis ID is not exist\n");
									break;
								}
								printf("\nPatient Record:\n");
								PrintPatientRecord(&h,p_id);
								break;
								
							/*View today’s reservations*/
							case 2:
								PrintReservations(&s);
								break;
							default:
								printf("\nInvalid Option\n");
								break;
						}
					}
					break;
					
				default:
					printf("\nInvalid Option\n");
					break;	
		}
		
		/*if flag = 0, the admin enter incorrect password for 3 times so exit from the system*/
		if(flag==0){
			break;
		}
	}
	
	

}






