#include "givenA1.h"
#include "stdio.h"

int main()
{
    /* task 1 variables*/
    char fName[30] = "a1Data.txt";
    struct Animal dataZoo[NUM_SAMPLES];
    int result = readFromFile(fName, dataZoo);
    if (result == 1)
    {
        printf("Successfully read a1Data.txt from readFromFile :)\n");
    }

    /* Task 2 variables */
    int whichFeature = 7; // specifying which feature to extract the mean / mode from
    float mean;
    int mode = 0;

    /* Task 3 variables*/
    // dataZoo

    /* Task 4 variables */
    // int vector1[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};

    // int vector2[NUM_FEATURES] = {1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 4, 0, 0, 1};

    /* Task 5 variables */
    // int vector1[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    // int vector2[NUM_FEATURES] = {1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 4, 0, 0, 1}; // hamming distance should be 8

    /* Task 6 variables */
    int vector1[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    int vector2[NUM_FEATURES] = {1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 4, 0, 0, 1}; // jaccards simalarity should be 0.38 for this.

    /* Task 7 variables */
    //int newSample[NUM_FEATURES] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //int k = 1;
    int whichDistanceFunction = 1;
    int kNearestNeighbors[NUM_SAMPLES];

    /* Task 8 variables */
    int neighborsForNewSample[NUM_SAMPLES] = {8, 12, 24, 39, 55};
    int newSample[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    //int k = 5;

    /* Task 9 vars*/
    int k = 5;
    struct Animal testData[NUM_TEST_DATA];

    int choice;

    do
    {
        printf("\nHere is the menu - enter a number between 1 and 10 \n\n");
        printf("1. Task 1 - read the information from a text file called a1Data.txt, store them in the array called dataZoo\n");
        printf("2. Task 2 - this function generates the mean and mode of that feature and outputs it to the calling function\n");
        printf("3. Task 3 - This function takes the zoo dataset and displays its class distribution as a histogram\n");
        printf("4. Task 4 - This function takes the zoo dataset and displays its class distribution as a histogram\n");
        printf("5. Task 5 - calculating the hamming distance \n");
        printf("6. Task 6 - calculating the jaccard similarity\n");
        printf("7. Task 7 - finding K nearest neighbors \n");
        printf("8. Task 8 - Given the k-nearest neighbors of a new data sample, this function predicts its class and returns it\n");
        printf("9. Task 9 - common in ML world to evaluate the performance of the algorithm using performance measures such as accuracy \n");
        printf("10. Exit\n");

        printf("Enter your choice: ");
        scanf(" %d", &choice);

        // validate choice here - should be a number between 1 and 10
        if (choice < 1 || choice > 10) {
            printf("Invalid choice. Please enter a number between 1 and 10.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            // call task 1 function here
            printf("I'm are reading a1data.txt %d", result);
            break;

        case 2:
            // call task 2 function here
            // checking if whichFeature is greater then 16 or less then 1, its invalid
            if (whichFeature > 16 || whichFeature < 1){
                printf("The whichfeature you selected is out of range... (Range is 1-16)\nYou selected %d", whichFeature);
                return -1;
            }
            // task 2
            int generateStatisticFeatureResult;
            generateStatisticFeatureResult = generateStatisticsFeatureX(dataZoo, whichFeature, &mean, &mode);
            printf("GenerateStatisticsFeatureX returns 1 if the feature # is valid, -1 if its incorrect: %d\n", generateStatisticFeatureResult);
            printf("Mean: %f\nMode: %d", mean, mode); // using * to derefrence the mean and mode to get the values from the function
            break;

        case 3:
            // call task 3 - class distribution
            classDistribution(dataZoo);
            break;

        case 4:
            // call task 4
            float euclideanDistanceResult;
            euclideanDistanceResult = euclideanDistance(vector1, vector2);
            printf("\nThe Euclidean distance is: %.2f\n", euclideanDistanceResult);
            break;

        case 5:
            // call task 5
            int hammingDistanceResult;
            hammingDistanceResult = hammingDistance(vector1, vector2);
            printf("\nThe hamming distance is : %d\n", hammingDistanceResult);
            break;

        case 6:
            // call task 6 here
            float jaccardSimilarityResult;
            jaccardSimilarityResult = jaccardSimilarity(vector1, vector2);
            printf("\nThe jaccardsSimalarity is : %.2f\n", jaccardSimilarityResult);
            break;

        case 7:
            // call task 7
            findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction, kNearestNeighbors);
            break;

        case 8:
            // call task 8
            int task8Result;
            task8Result = predictClass(dataZoo, neighborsForNewSample, newSample, k);
            printf("\nThe predictClass is : %d\n", task8Result);
            break;

        case 9:
            // call task 9
            FILE *fptr = fopen("testData.txt", "r");
            if (fptr == NULL){
                printf("Couldn't read the file\n");
                return -1; // Return an error code or handle the error appropriately
            }

            for (int i = 0; i < NUM_TEST_DATA; i++) {
                char name[20]; // Buffer to hold the animal name
                // Use fscanf to read the animal name and the class label
                fscanf(fptr, "%s ", name); // Read the animal name and ignore spaces
                for (int j = 0; j < 17; j++) {
                    fscanf(fptr, "%d ", &testData[i].features[j]); // Read the features as floats and ignore spaces
                }
                fscanf(fptr, "%d", &testData[i].classLabel); // Read the class label
            }
            fclose(fptr); // closing my file

            float task9Result;
            task9Result = findAccuracy(dataZoo, testData, k);
            printf("The accuracy is %.2f", task9Result);
            break;

        case 10:
            printf("Exiting...\n");
            break;

        default:
            printf("That is an invalid choice\n");
        }

    } while (choice != 10);

    return 0;
}
