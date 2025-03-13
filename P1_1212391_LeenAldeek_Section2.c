#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//Name: Leen Aldeek
//ID#: 1212391
//Section: 2

/*
This is a struct for the city/district name with pointers next1, prev1, and next0.
the last one points to the town belonging to a certain town.
*/
struct DisNode
{
    char districts[50];
    struct twonNode* next0;
    struct DisNode* next1;
    struct DisNode* prev1;

};
/*
This is a struct for the town name with pointers next2 and prev2
also, it has a part of the town population.
*/
struct twonNode
{
    char twons[50];
    int population;
    struct twonNode* next2;
    struct twonNode* prev2;

};
void menu();
void creatDDL(struct DisNode** H);/*this function reads the file and creates a doubly linked list
of districts and towns that are in the file, each city followed by the next city, and each city points
 to the towns that belong to that city also each town in a certain city points to the next town.
*/
void option1();//to Load the input file
void option2();// to Print the loaded information before sorting.
void option3(struct DisNode** head);// to Sort the districts alphabetically using Radix sort.
void option4(struct DisNode** head);// to Sort the towns for each district based on population in ascending order.
void printDDL(struct DisNode* H);//option5 to Print the sorted information.
void option6(struct DisNode** L);// to Add a new district to the list of sorted districts.
void option7(struct DisNode* head);// to Add a new town to a certain district.
void option8(struct DisNode** head);// to Delete a town from a specific district.
void option9(struct DisNode** head) ;// to Delete a complete district.
void option10(struct DisNode* head);// to Calculate the population of Palestine, the max and min town population.
void option11(struct DisNode** head);// to Print the districts and their total population.
void option12(struct DisNode** head);// to Change the population of a town.
void option13(struct DisNode* head);// to Save to output file.

int main()
{
    int option;
    struct DisNode* districts = NULL;
    creatDDL(&districts);// creat the list then do the operations ...
    do
    {
        menu();
        printf("Enter your option: ");
        scanf("%d", &option);
        if (option == 1)
        {
            option1();
        }
        else if (option == 2)
        {
            option2();
        }
        else if(option == 3)
        {
            option3(&districts);
            printDDL(districts);
        }
        else if(option == 4)
        {
            option4(&districts);
        }
        else if(option == 5)
        {
            option4(&districts);
            printDDL(districts);
        }
        else if(option == 6)
        {
            option6(&districts);
        }
        else if(option == 7)
        {
            option7(districts);
        }
        else if(option == 8)
        {
            option8(&districts);
        }
        else if(option == 9)
        {
            option9(&districts);
        }
        else if(option == 10)
        {
            option10(districts);
        }

        else if(option == 11)
        {
            option11(&districts);
        }
        else if(option == 12)
        {
            option12(&districts);
        }
        else if(option == 13)
        {
            option13(districts);
        }

        else if (option != 14)
        {
            printf("Invalid option. Please try again.\n");
        }

    }
    while (option != 14);
    printf("Exiting the program.\n");
    return 0;
}
void option1()
{
    FILE *InputFile;
    char filename[100];
    printf("Enter the file name: ");
    scanf("%s",filename);

    InputFile = fopen(filename, "r");
    if (InputFile != NULL)
    {
        printf("The file loaded successfully.\n");
        fclose(InputFile);
    }
    else
    {
        printf("Error loading the file.\n");
    }

}
void option2()
{
    FILE *InputFile;
    char filename[100];
    printf("Enter the file name: ");
    scanf("%s",filename);
    InputFile = fopen(filename, "r");
    if (InputFile != NULL)
    {
        printf("File contents:\n\n");
        char info = fgetc(InputFile);
        while (info != EOF)
        {
            printf("%c", info);
            info = fgetc(InputFile);
        }
        fclose(InputFile);
    }
    else
    {
        printf("Error opening the file.\n");
    }
    printf("\n");
}
void menu()
{
    printf("1) Load the input file.\n");
    printf("2) Print the loaded information before sorting.\n");
    printf("3) Sort the districts alphabetically using Radix sort.\n");
    printf("4) Sort the towns for each district based on population in ascending order.\n");
    printf("5) Print the sorted information.\n");
    printf("6) Add a new district to the list of sorted districts.\n");
    printf("7) Add a new town to a certain district.\n");
    printf("8) Delete a town from a specific district.\n");
    printf("9) Delete a complete district.\n");
    printf("10) Calculate the population of Palestine, the max and min town population.\n");
    printf("11) Print the districts and their total population.\n");
    printf("12) Change the population of a town, after prompting the user to enter the district name.\n");
    printf("13) Save to output file.\n");
    printf("14) Exit.\n");
    printf("_______________________________________________________________________________________________\n");

}
void creatDDL(struct DisNode** H)
{
    FILE *in;
    char String[100];
    char District[25];
    char town[25];
    char population[50];
    in = fopen("districts.txt","r");
    if(in == NULL)
    {
        printf("Error opening the file...\n");
        return;
    }
    while(fgets(String,sizeof(String),in) != NULL )
    {
        char *div = strtok(String,"|");
        if(div == NULL)
        {
            printf("Something went wrong while parsing the line...\n");
            fclose(in);
            return;
        }
        strcpy(District,div);
        div = strtok(NULL,"|");
        strcpy(town,div);
        div = strtok(NULL,"|");
        strcpy(population,div);

        int INTpopulation = atoi(population);
        struct DisNode* temp_city_found = NULL;
        struct DisNode* temp_city = *H;
        while(temp_city != NULL)
        {
            if (strcmp(temp_city->districts, District) == 0)
            {
                temp_city_found = temp_city;
                break;
            }
            temp_city = temp_city->next1;
        }

        if (temp_city_found != NULL)
        {
            struct twonNode* t = (struct twonNode*)malloc(sizeof(struct twonNode));
            if (t == NULL)
            {
                printf("Memory allocation failed...\n");
                fclose(in);
                return;
            }
            strcpy(t->twons, town);
            t->population = INTpopulation;
            t->next2 = temp_city_found->next0;
            t->prev2 = NULL;
            if (temp_city_found->next0 != NULL)
            {
                temp_city_found->next0->prev2 = t;
            }
            temp_city_found->next0 = t;
        }
        else
        {
            struct DisNode* dis = (struct DisNode*)malloc(sizeof(struct DisNode));
            if (dis == NULL)
            {
                printf("Memory allocation failed...\n");
                fclose(in);
                return;
            }
            strcpy(dis->districts, District);
            dis->next0 = (struct twonNode*)malloc(sizeof(struct twonNode));
            if (dis->next0 == NULL)
            {
                printf("Memory allocation failed...\n");
                free(dis);
                fclose(in);
                return;
            }
            strcpy(dis->next0->twons, town);
            dis->next0->population = INTpopulation;
            dis->next0->next2 = NULL;
            dis->next0->prev2 = NULL;
            dis->prev1 = NULL;
            dis->next1 = NULL;
            if (*H == NULL)
            {
                *H = dis;
            }
            else
            {
                struct DisNode* temp = *H;
                while (temp->next1 != NULL)
                {
                    temp = temp->next1;
                }
                temp->next1 = dis;
                dis->prev1 = temp;
            }
        }
    }
    fclose(in);
}
void option4(struct DisNode** head)
{
    struct DisNode* city = *head;

    while (city != NULL)
    {
        struct twonNode* sortedTownList = NULL; // Temporary sorted list for towns
        struct twonNode* currentTown = city->next0;

        // Create a sorted list of towns based on population
        while (currentTown != NULL)
        {
            struct twonNode* nextTown = currentTown->next2;

            // Insert current town into sorted list based on population
            if (sortedTownList == NULL || currentTown->population < sortedTownList->population)
            {
                currentTown->next2 = sortedTownList;
                sortedTownList = currentTown;
            }
            else
            {
                struct twonNode* temp = sortedTownList;
                while (temp->next2 != NULL && temp->next2->population < currentTown->population)
                {
                    temp = temp->next2;
                }
                currentTown->next2 = temp->next2;
                temp->next2 = currentTown;
            }

            currentTown = nextTown;
        }

        // Update the next0 pointer of the city to point to the sorted list of towns
        city->next0 = sortedTownList;

        // Move to the next city
        city = city->next1;
    }
    printf("towns have been sorted successfully ^_^\n");
}
void printDDL(struct DisNode* H)
{
    struct DisNode* currentCity = H;
    while (currentCity != NULL)
    {
        printf("District: %s\n", currentCity->districts);
        printf("Towns:\n");
        struct twonNode* currentTown = currentCity->next0;
        while (currentTown != NULL)
        {
            printf("\tTown: %s, Population: %d\n", currentTown->twons, currentTown->population);
            currentTown = currentTown->next2;
        }
        currentCity = currentCity->next1;
        printf("\n");
    }
}
void option6(struct DisNode** L)
{
    struct DisNode* citytemp = *L;
    char disName[20];
    printf("Enter the city name:");
    scanf("%s", disName);
    while (citytemp != NULL)
    {
        if (strcmp(citytemp->districts, disName) == 0)//Why add an existing city?
        {
            printf("The city you want to add already exists, try to add another city....");
        }
        citytemp = citytemp->next1;//move on to the next city to check if it is exist or not.
    }
//if the city does not exist then create a new node to add it.
    struct DisNode* city = (struct DisNode*)malloc(sizeof(struct DisNode));
    if (city == NULL)
    {
        printf("Node creation failed....");
    }
    //add the new city at the beginning of the list, adding it like that is the easiest way, and it doesn't take time.
    strcpy(city->districts, disName);
    city->next0 = NULL;//no towns yet.
    city->next1 = *L;//now the new city is the first one in the list.
    city->prev1 = NULL;//no previous , because it is the first one.
    if (*L != NULL)
    {
        (*L)->prev1 = city; // Update the prev1 pointer of the previous city.
    }
    *L = city;//update the head (L) pointer to point to the new city(first city).
    //user can use option 3 to sort the districts again.
    printf("City added successfully.\n");
}
void option7(struct DisNode* head)
{
    char disName[50];
    printf("Enter the district name: ");
    scanf("%s", disName);

    struct DisNode* citytemp = head;
    bool districtFound = false; // Flag to track if the district is found
    while (citytemp != NULL)
    {
        if (strcmp(citytemp->districts, disName) == 0)
        {
            districtFound = true; // Mark the district as found
            struct twonNode* Town = (struct twonNode*)malloc(sizeof(struct twonNode));
            if (Town == NULL)
            {
                printf("Memory allocation failed.\n");
            }
            printf("Enter the town name: ");
            scanf("%s", Town->twons);
            printf("Enter the town population: ");
            scanf("%d", &Town->population);

            // Insert new town at the beginning of the town list
            Town->next2 = citytemp->next0;
            Town->prev2 = NULL;
            if (citytemp->next0 != NULL)
            {
                citytemp->next0->prev2 = Town;
            }
            citytemp->next0 = Town;

            printf("New town added to district %s successfully.\n", disName);
        }
        citytemp = citytemp->next1;
    }

    // Check if the district was found
    if (!districtFound)
    {
        printf("District '%s' not found try again....\n", disName);
    }
}
void option8(struct DisNode** head)
{

    struct DisNode* citytemp = *head;
    printf("Enter the district name: ");
    char city[20];
    scanf("%s", city);
    // Search for the district
    while (citytemp != NULL)
    {
        if (strcmp(citytemp->districts, city) == 0)
        {
            printf("Enter the town name: ");
            char town[20];
            scanf("%s", town);
            struct twonNode** towntemp = &(citytemp->next0);

            // Search for the town within the district
            while (*towntemp != NULL)
            {
                if (strcmp((*towntemp)->twons, town) == 0)
                {
                    // Town found, delete it
                    struct twonNode* temp = *towntemp;
                    *towntemp = (*towntemp)->next2; // Update pointer to skip the target town node
                    free(temp); // Free memory for the target town node
                    printf("Town '%s' deleted from district '%s' successfully.\n", town, city);
                    return;
                }
                towntemp = &((*towntemp)->next2); // Move to the next town
            }

            // If control reaches here, town was not found
            printf("Town '%s' not found in district '%s'.\n", town, city);
            return;
        }
        citytemp = citytemp->next1;
    }

    // If control reaches here, district was not found
    printf("District '%s' not found.\n", city);
}
void option9(struct DisNode** head)
{
    printf("Enter the city name that you want to delete:");
    char dis[20];
    scanf("%s", dis);
    struct DisNode* city = *head;
    struct DisNode* citytemp = NULL;

    while (city != NULL)
    {
        if (strcmp(city->districts, dis) == 0)
        {
            struct twonNode* town = city->next0;
            struct twonNode* towntemp;

            // Delete all the towns within the city
            while (town != NULL)
            {
                towntemp = town;
                town = town->next2;
                free(towntemp);
            }

            if (citytemp == NULL)
            {
                *head = city->next1; // Update head if deleting the first district
            }
            else
            {
                citytemp->next1 = city->next1; // Update pointers to skip the deleted district
            }

            free(city); // Free memory for the deleted district
            printf("District '%s' deleted successfully.\n", dis);
            return; // Exit function after deleting the district
        }
        citytemp = city;
        city = city->next1;
    }

    // district was not found
    printf("District '%s' not found.\n", dis);
}
void option10(struct DisNode* head)
{
    int max = 0;
    int min = 2147483647;
    char maxtown[20];
    char mintown[20];
    struct DisNode* citytemp = head;
    while(citytemp != NULL)
    {
        struct twonNode* towntemp = citytemp->next0;
        while(towntemp != NULL)
        {
            if(towntemp->population > max)//if the current town population is >than max then update the max value to = this town population.
            {
                max = towntemp->population;
                strcpy(maxtown,towntemp->twons);//move the current town to be the maximum town population.
            }
            if (towntemp->population < min)//if the current town population is less than min then update min value to be the population for this town.
            {
                min = towntemp->population;
                strcpy(mintown,towntemp->twons);// move the current town to be the minimum town population.
            }
            towntemp = towntemp->next2;
        }
        citytemp = citytemp->next1;//move on to the next city , if the city is not found yet.
    }
    printf("Maximum town population: %d (Town: %s)\n", max, maxtown);
    printf("Minimum town population: %d (Town: %s)\n", min, mintown);

}
void option11(struct DisNode** head)
{
    struct DisNode* citytemp = *head;
    while(citytemp != NULL)
    {
        struct twonNode* towntemp = citytemp->next0;
        int totalpop = 0;
        while(towntemp != NULL)
        {
            totalpop += towntemp->population;
            towntemp = towntemp->next2;

        }
        printf("%s population = %d\n", citytemp->districts, totalpop);
        citytemp = citytemp->next1;
    }
}
void option12(struct DisNode** head)
{
    printf("Enter the city name:");
    char city[20];
    scanf("%s",city);

    struct DisNode* citytemp = *head;
    while(citytemp != NULL)
    {
        if(strcmp(citytemp->districts,city) == 0)
        {
            printf("Enter the town name:");
            char town[20];
            scanf("%s",town);

            struct twonNode* towntemp = citytemp->next0;
            while(towntemp != NULL)
            {
                if(strcmp(towntemp->twons,town) == 0)
                {
                    printf("Enter the updated population:");
                    int pop;
                    scanf("%d",&pop);
                    towntemp->population = pop;
                    printf("Population of town '%s' in district '%s' updated successfully.\n", town, city);
                    return;
                }
                towntemp = towntemp->next2;
            }


            printf("Town '%s' not found in district '%s'.\n", town, city);
            return;
        }
        citytemp = citytemp->next1;
    }


    printf("District '%s' not found.\n", city);
}
void option3(struct DisNode** head)
{
    int strLength = 50;

    for (int i = strLength - 1; i >= 0; --i)
    {
        struct DisNode* output = NULL;
        struct DisNode* count[256] = { NULL };
        struct DisNode* citytemp = *head;
        while (citytemp != NULL)
        {
            int index = (unsigned char)citytemp->districts[i];
            struct DisNode* temp = citytemp->next1;
            citytemp->next1 = count[index];
            if (count[index] != NULL)
                count[index]->prev1 = citytemp;//maybe there is a city in this location.
            count[index] = citytemp;
            citytemp = temp;
        }

        //iterating through the count array in reverse order
        for (int j = 255; j >= 0; --j)
        {
            struct DisNode* pointer = count[j];
            while (pointer != NULL)
            {
                struct DisNode* temp = pointer->next1;
                pointer->next1 = output;
                if (output != NULL)
                    output->prev1 = pointer;
                output = pointer;
                pointer = temp;
            }
        }
         // Update the head pointer to point to the head of the sorted list
        *head = output;
        // Find the tail of the sorted list
        struct DisNode* tail = output;
        while (tail && tail->next1)
            tail = tail->next1;
        // make sure that the tail's next pointer is NULL to mark the end of the list
        if (tail)
            tail->next1 = NULL;
    }
}

void option13(struct DisNode* head)
{
    FILE *outputFile;
    char filename[100];

    printf("Enter the output file name: ");
    scanf("%s", filename);

    outputFile = fopen(filename, "w");
    if (outputFile == NULL)  printf("Error creating the output file.\n");
    print13(head, outputFile);
    fclose(outputFile);
    printf("Data saved to %s successfully.\n", filename);

}
void print13(struct DisNode* head, FILE *outputFile)
{
    struct DisNode* citytemp = head;
    while (citytemp != NULL)
    {
        fprintf(outputFile, "%s District, Population = ", citytemp->districts);
        int total = 0;
        struct twonNode* towntemp = citytemp->next0;
        while (towntemp != NULL)
        {
            total += towntemp->population;
            towntemp = towntemp->next2;
        }
        fprintf(outputFile, "%d\n", total);

        towntemp = citytemp->next0;
        while (towntemp != NULL)
        {
            fprintf(outputFile, "%s, %d\n", towntemp->twons, towntemp->population);
            towntemp = towntemp->next2;
        }
        citytemp = citytemp->next1;
    }
}
