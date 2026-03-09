#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int mode;
int admin_restriction=0;
int password;
int admin_list;
int user_mode;
char v0[50];
int v1;
int v2;
int v3;
char new_v0[50];
int new_v1;
int new_v2;
int new_v3;
int searchId;
int edit_or_exit;
int edit;
int time_slot;
char ranges[5][20] = {
    "2 - 2:30 PM",
    "2:30 - 3 PM",
    "3 - 3:30 PM",
    "3:30 - 4 PM",
    "4 - 4:30 PM"
	};
char gender[2][6]={"male","female"};
int slot_status[5] = {0,0,0,0,0};  
int slot_patient_id[5] = {0,0,0,0,0}; 

struct Patient {
    char name[50];
    int age;
    int gender;
    int id;
	int time_slots;
	struct Patient* next;  
};

struct Patient* head = NULL;

struct Patient* createpatient(char v0[], int v1, int v2, int v3) {
    struct Patient* newpatient = (struct Patient*)malloc(sizeof(struct Patient));
    strcpy(newpatient->name, v0);
    newpatient->age = v1;
    newpatient->gender = v2;
    newpatient->id = v3;
    newpatient->next = NULL;

    return newpatient;
}

void insert_patient_AtEnd(struct Patient* * head, char v0[], int v1, int v2, int v3) {
    struct Patient* newpatient = createpatient(v0, v1, v2, v3);
    if (*head == NULL) {
        *head = newpatient;
    } else {
        struct Patient* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newpatient;
    }
}

void update_patient(struct Patient* head, int id,const char* new_v0, int new_v1, int new_v2) {
    struct Patient* current = head;
    while (current != NULL) {
        if (current->id == id) {
            printf("Found: Name: %s, Age: %d, Gender: %s, ID: %d\n",
            current->name, current->age,  gender[current->gender], current->id);
            
			strcpy(current->name, new_v0);
            current->age = new_v1;
			current->gender = new_v2;
            
			
			printf("Patient information updated!\n");
            printf("New details: Name: %s, Age: %d, Gender: %s\n",
            current->name, current->age,  gender[current->gender]);
            return; 
        }
        current = current->next;
    }
    printf("Patient with ID %d not found.\n", id);
}

	int ID_Taken(struct Patient* head, int id) {
    struct Patient* current = head;
    while (current != NULL) {
        if (current->id == id) {
            
			return 1; 
        }
        current = current->next;
    }
    return 0;  
	}
	int dsiplay_patient(struct Patient* head, int id) {
    struct Patient* current = head;
    while (current != NULL) {
        if (current->id == id) {
			printf("Found: Name: %s, Age: %d, Gender: %s, ID: %d\n",
            current->name, current->age,  gender[current->gender], current->id);
            
			return 1; 
        }
        current = current->next;
    }
    return 0;  
	}
	


void reserve_slot(struct Patient* head, int id, int slot_index) {
    struct Patient* current = head;
    while (current != NULL) {
        if (current->id == id) {
            if (slot_index < 0 || slot_index >= 5) {
                printf("Invalid slot index.\n");
                return;
            }
            if (slot_status[slot_index] == 0) {
                slot_status[slot_index] = 1;       
                slot_patient_id[slot_index] = id;   
                printf("Slot %s reserved for patient ID %d\n", ranges[slot_index], id);
            } else {
                printf("Slot %s is already reserved by patient ID %d\n", ranges[slot_index], slot_patient_id[slot_index]);
            }
            return;
        }
        current = current->next;
    }
    printf("Patient with ID %d not found.\n", id);
}


void cancel_reservation(int id, int slot_index) {
    if (slot_index < 0 || slot_index >= 5) {
        printf("Invalid slot index.\n");
        return;
    }
    if (slot_patient_id[slot_index] == id) {
        slot_status[slot_index] = 0;
        slot_patient_id[slot_index] = 0;
        printf("Reservation for patient %d at slot %d canceled.\n", id, slot_index);
    } else {
        printf("No reservation found for patient %d at slot %d.\n", id, slot_index);
    }
}

void view_today_reservations() {
    printf("Today's Reservations\n");
    for (int i = 0; i < 5; i++) {
        if (slot_status[i] == 1) {
            printf("Slot %s  Patient ID: %d\n", ranges[i], slot_patient_id[i]);
        } else {
            printf("Slot %s  Available\n", ranges[i]);
        }
    }
    printf("\n");
}
struct Patient* find_patient_by_id(struct Patient* head, int id) {
    struct Patient* cur = head;
    while (cur != NULL) {
        if (cur->id == id) return cur;
        cur = cur->next;
    }
    return NULL;
}


int main(){
		struct Patient* head = NULL;
			for (mode;mode<3;){
				printf("welcome to our clinc system. choose the mode \n0)admin mode\n1)usermode\n2)close program\n");
				scanf("%d",&mode);
				
				if (mode==0){
					
					printf("Admin profile\nplease insert the password of 4 digits:  \n");
					do{
						scanf("%d",&password);
					if (password!=1234){
						admin_restriction++;
						printf("wrong password you have %d more trails:  \n ",3-admin_restriction );
										}
					else{
						printf("password insertion successfully\n here's admin list:\n0)add new patient record\n1)edit existing patient record\n2)reserve a slot with the doctor\n3)cancel reservation\n4)back to main menu\n");
						scanf("%d",&admin_list);
						if(admin_list==0){
							printf("With out spaces! Enter name: ");
							scanf("%s", v0);
							printf("Enter age: ");
							scanf("%d", &v1);
							printf("Select gender (0=male, 1=female): ");
							int g;
							scanf("%d", &g);
							if (g == 0 || g == 1) {
								v2 = g;
							} else {
								printf("Invalid choice, defaulting to male.\n");
								v2 = 0;
							}
							printf("Enter 9 Digits ID: ");
							scanf("%d", &v3);
								if (ID_Taken(head, v3)) {
									printf("Error: ID %d is already taken! Please use a different ID.\n", v3);
																} 
								else {
									insert_patient_AtEnd(&head, v0, v1, v2, v3);
									printf("Patient added successfully!\n\n");
									break;
										}
											}
								
						if (admin_list == 1) {
									printf("Enter ID to search: ");
									scanf("%d", &searchId);

									struct Patient* p = find_patient_by_id(head, searchId);
									if (p == NULL) {
										printf("Patient with ID %d not found.\n", searchId);
									} else {
									
										printf("Found: Name: %s, Age: %d, Gender: %s, ID: %d\n",
											   p->name, p->age, gender[p->gender], p->id);

										printf("0) edit patient\n1) exit\n");
										scanf("%d", &edit_or_exit);
										if (edit_or_exit == 0) {
											printf("select what to edit\n0)name\n1)age\n2)gender\n3)exit\n");
											scanf("%d", &edit);

											if (edit == 0) {
												printf("Enter new name: ");
												scanf("%s", new_v0);     
												strcpy(p->name, new_v0);
												printf("Name updated.\n");
												break;
																} 
											else if (edit == 1) {
												printf("Enter new age: ");
												scanf("%d", &new_v1);
												p->age = new_v1;
												printf("Age updated.\n");
												break;
																		} 
											else if (edit == 2) {
												printf("Select gender (0=male, 1=female): ");
												int g;
												scanf("%d", &g);
												if (g == 0 || g == 1) {
													p->gender = g;
													printf("Gender updated.\n");
												} else {
													printf("Invalid gender. Not updated.\n");
												}
												break;
									
											}
											else {
										
											}
										}
									}
								}
										
						else if(admin_list==2){
							view_today_reservations();
							printf("Enter patient ID: ");
							scanf("%d", &searchId);
							printf("Enter slot number (0-4): ");
							scanf("%d", &time_slot);
							reserve_slot(head, searchId, time_slot);
							break;
												}		
						else if(admin_list==3){
							printf("Enter patient ID: ");
							scanf("%d", &searchId);
							printf("Enter slot number to cancel (0-4): ");
							scanf("%d", &time_slot);
							cancel_reservation(searchId, time_slot);
							break;
												}
						else if(admin_list==4){
						break;	
						}
														
						}
						}
					while(admin_restriction<3);		
					}
			

		
				else if(mode==1){
				do{
				printf("Select how you want to proceed:\n0) View patient record\n1)View today  reservations\n2)back to main menu\n");
				scanf("%d",&user_mode);
				if(user_mode==0){
						printf("Enter ID to search: ");
						scanf("%d", &searchId);
						dsiplay_patient(head, searchId);
				}
				else if(user_mode==1){
				view_today_reservations();
					break;
					
				}
				else if(user_mode==2){
						break;
				}
				else{
					printf("invalid user mode selection");
				}
							}
			while(1);				}
			else if(mode>=2){
				break;
			}
			}
								
			}
				