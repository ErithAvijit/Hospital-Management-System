#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Patient {
    int id;
    char name[100];
    int age;
    char disease[100];
    struct Patient* next;
} Patient;

typedef struct Bed {
    int bed_id;
    int is_allocated;
    Patient* patient;
    struct Bed* next;
} Bed;

typedef struct LogBook {
    int patient_id;
    char test[100];
    char medicine[100];
    struct LogBook* next;
} LogBook;

typedef struct Bill {
    int patient_id;
    int days;
    float daily_rate;
    float total;
    struct Bill* next;
} Bill;

Patient* patientHead = NULL;
Bed* bedHead = NULL;
LogBook* logHead = NULL;
Bill* billHead = NULL;
int bed_count = 10;

void add_patient();
void update_patient();
void allocate_bed();
void add_log();
void find_patient();
void discharge_summary();
void total_bill();
void all_menu();

int main() {
    int choice;
    for (int i = 1; i <= bed_count; i++) {
        Bed* newBed = (Bed*)malloc(sizeof(Bed));
        newBed->bed_id = i;
        newBed->is_allocated = 0;
        newBed->patient = NULL;
        newBed->next = bedHead;
        bedHead = newBed;
    }
    while (1) {
        all_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_patient();
                break;
            case 2:
                find_patient();
                break;
            case 3:
                update_patient();
                break;
            case 4:
                allocate_bed();
                break;
            case 5:
                add_log();
                break;
            case 6:
                discharge_summary();
                break;
            case 7:
                total_bill();
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
	fflush(stdin);
    return 0;
}

void all_menu() {
    printf("\nHospital Management System\n");
    printf("1. Add The Patient Information:\n");
    printf("2. Search Patient Details:\n");
    printf("3. Update Patient Details:\n");
    printf("4. Allocate A Bed:\n");
    printf("5. Log Book for Tests and Medicine:\n");
    printf("6. Generate Discharge Summary For Patient:\n");
    printf("7. Create Bill:\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}

void add_patient() {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    printf("Enter Patient ID: ");
    scanf("%d", &newPatient->id);
    printf("Enter Patient Name: ");
    scanf("%s", newPatient->name);
    printf("Enter Age: ");
    scanf("%d", &newPatient->age);
    printf("Enter Disease: ");
    scanf("%s", newPatient->disease);
    newPatient->next = patientHead;
    patientHead = newPatient;
    printf("Patient added successfully!\n");
}

void update_patient() {
    int id;
    printf("Enter Patient ID to update: ");
    scanf("%d", &id);
    Patient* temp = patientHead;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Enter new name: ");
            scanf("%s", temp->name);
            printf("Enter new age: ");
            scanf("%d", &temp->age);
            printf("Enter new disease: ");
            scanf("%s", temp->disease);
            printf("Patient updated successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Patient not found!\n");
}

void allocate_bed() {
    int patient_id;
    printf("Enter Patient ID to allocate bed: ");
    scanf("%d", &patient_id);

    Patient* patient = patientHead;
    while (patient != NULL) {
        if (patient->id == patient_id) {
            break;
        }
        patient = patient->next;
    }

    if (patient == NULL) {
        printf("Patient not found!\n");
        return;
    }

    Bed* temp = bedHead;
    while (temp != NULL) {
        if (!temp->is_allocated) {
            temp->is_allocated = 1;
            temp->patient = patient;
            printf("Bed No %d is allocated to patient %d\n", temp->bed_id, patient->id);
            return;
        }
        temp = temp->next;
    }

    printf("No beds available!\n");
}

void add_log() {
    LogBook* newLog = (LogBook*)malloc(sizeof(LogBook));
    printf("Enter Patient ID: ");
    scanf("%d", &newLog->patient_id);
    printf("Enter Test: ");
    scanf("%s", newLog->test);
    printf("Enter Medicine: ");
    scanf("%s", newLog->medicine);
    newLog->next = logHead;
    logHead = newLog;
    printf("Log added successfully!\n");
}

void find_patient() {
    int id;
    printf("Enter Patient ID to search: ");
    scanf("%d", &id);
    Patient* temp = patientHead;
    LogBook* temp1 = logHead;
    //Bed* temp2 = bedHead;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Patient ID: %d\n", temp->id);
            printf("Name: %s\n", temp->name);
            printf("Age: %d\n", temp->age);
            printf("Disease: %s\n", temp->disease);
            if(temp1 != NULL && temp1->patient_id == id){
                printf("Test: %s\n", temp1->test);
                printf("Medicine: %s\n", temp1->medicine);
            }
            /*if(temp2 != NULL){
                printf("Bed No %d is allocated to patient\n", temp2->bed_id);
            }*/
            return;
        }
        temp = temp->next;
    }
    printf("Patient not found!\n");
}

void discharge_summary() {
    int patient_id;
    printf("Enter Patient ID to generate discharge summary: ");
    scanf("%d", &patient_id);

    Patient* patient = patientHead;
    while (patient != NULL) {
        if (patient->id == patient_id) {
            printf("Discharge Summary\n");
            printf("Patient ID: %d\n", patient->id);
            printf("Name: %s\n", patient->name);
            printf("Age: %d\n", patient->age);
            printf("Disease: %s\n", patient->disease);
            return;
        }
        patient = patient->next;
    }
    printf("Patient not found!\n");
}

void total_bill() {
    int patient_id, days;
    float daily_rate;
    printf("Enter Patient ID: ");
    scanf("%d", &patient_id);
    printf("Enter Number of Days: ");
    scanf("%d", &days);
    printf("Enter Daily Rate: ");
    scanf("%f", &daily_rate);

    Bill* newBill = (Bill*)malloc(sizeof(Bill));
    newBill->patient_id = patient_id;
    newBill->days = days;
    newBill->daily_rate = daily_rate;
    newBill->total = days * daily_rate;
    newBill->next = billHead;
    billHead = newBill;

    printf("Total Bill for patient %d: %.2f\n", patient_id, newBill->total);
}
