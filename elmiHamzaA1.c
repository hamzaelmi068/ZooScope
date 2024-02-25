#include <stdio.h>
#include "givenA1.h"
#include "helper.h"


int readFromFile(char fName[30], struct Animal dataZoo[NUM_SAMPLES])
{
    FILE *fptr;
    fptr = fopen(fName, "r"); // reading an exisiting file

    // checking if the file is empty
    if (fptr == NULL)
    {
        printf("error, sorry I couldn't open your file");
        return -1;
    }

    int i = 0;
    // while it isnt the end of the file
    while (!feof(fptr))
    {
        // ill first start off by reading the animal name
        fscanf(fptr, "%s", dataZoo[i].animalName);
        // next, we need to read the features
        // while loop to loop through the features
        int j = 0;
        while (j < NUM_FEATURES)
        {
            fscanf(fptr, "%d", &dataZoo[i].features[j]);
            j++;
        }
        // Finally, all we need to now is read the class labels
        fscanf(fptr, "%d", &dataZoo[i].classLabel);
        // to move on to the next struct in the array, we increment i here
        i++;
    }

    // After reading the data, this is just to check if it was read correctly // testing
    /*for (int k = 0; k < NUM_SAMPLES; k++)
    {
        printf("Animal Name: %s\n", dataZoo[k].animalName);
        printf("Features: ");
        for (int l = 0; l < NUM_FEATURES; l++)
        {
            printf("%d ", dataZoo[k].features[l]);
        }
        printf("\nClass Label: %d\n", dataZoo[k].classLabel);
    } */

    // finally, just need to close the file
    fclose(fptr);
    return 1;
}

int generateStatisticsFeatureX(struct Animal dataZoo[NUM_SAMPLES], int whichFeature, float *mean, int *mode)
{
    /*Given the array dataZoo populated with data read in Task 1, and a feature number, this
    function generates the mean and mode of that feature and outputs it to the calling
    function. It returns -1 if the given feature number is incorrect. Note that the valid features
    are numbered from 1 to 16.*/

    // mean is pretty much the average, so ill  loop through the samples, add them up and divide it by the number of features
    int sum = 0;
    int count[NUM_SAMPLES + 1] = {0};
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        // finding the mean first, by adding up all the numbers in the whichFeatures coloumn
        sum = sum + dataZoo[i].features[whichFeature - 1];                                               // were subtracting one because array indices start at 0
        count[dataZoo[i].features[whichFeature - 1]] = count[dataZoo[i].features[whichFeature - 1]] + 1; // used to keep track of how many times a feature value is shown
    }
    // average would be the total number of features, divided by the total (NUM_SAMPLES, which is 100).
    *mean = (float)sum / NUM_SAMPLES;

    // finding the mode
    int maxCounter = 0;  // keeping track of maximum count so far
    int numCountMax = 0; // keeping track of the number of elemnts that have the maximum occurence
    
    int i = 0;
    while ( i < NUM_SAMPLES){
        // if the count at this index is greater then maxCount, it updates maxCounter to the current count and index
        if (count[i] > maxCounter)
        {
            maxCounter = count[i];
            numCountMax = 1;
            *mode = i;
        }
        else if (count[i] == maxCounter)
        { // if count current element is equal to maxCounter, this means that this element has the same frequency
            numCountMax++;
        }
        i++;
    }
    
    // checking the maximum occurence
    if (numCountMax == 0)
    { // if theres no mode at all , we set the mode equal to -1
        *mode = -1;
    }
    return 1;
}

// Counts the number of digits in an integer.
size_t digits(int num) {
    size_t count = 0;
    while (num != 0) {
        num /= 10;
        ++count;
    }
    return count;
}

void classDistribution(struct Animal dataZoo[NUM_SAMPLES])
{   /*  instructions: This function takes the zoo dataset and displays its class distribution as a histogram as
    shown below. Note that member name classLabel in struct Animal stores the class
    label for each sample or row. There are 40 rows with classLabel as 1, 20 rows with
    classLabel l as 2, and so on*/

    int sum[NUM_CLASSES] = {0};
    // Loop over all samples in the zoo dataset
    for (int i = 0; i < NUM_SAMPLES; i++)
    {   // Increment the sum for the class label of the current sample
        sum[dataZoo[i].classLabel - 1] += 1;
    }

    // Initialize the maximum value to 0
    int maxValue = 0;

    // Loop over all class labels
    for (int j = 0; j < NUM_CLASSES; j++)
    {
        // Update the maximum value if the current class label has a higher sum
        if (sum[j] > maxValue)
        {
            maxValue = sum[j];
        }
    }

    // Loop from the maximum value down to 1
    for (int i = maxValue; i > 0; i--)
    {
        // Reset the count of written digits for each level
        int written = 0;
    
        // Loop over all class labels
        for (int j = 0; j < NUM_CLASSES; j++)
        {   int padding;
            // Calculate the padding needed for each class label
            if (j){
                 padding = 10;
            }
            else{
                 padding = 10 / 2;
            }
            // (written - 1) the first digit is always aligned
            // Adjust the padding if any digits have been written
            if (written) { 
                padding = padding - (written - 1) - 1; 
            }

            // If the sum of the current class label equals the current level, print the sum value
            if (sum[j] + 1 == i) {
                printf("%*c%d)", padding - 1, '(', sum[j]); // https://en.cppreference.com/w/c/io/fprintf - helped understand padding / formatting strings in c
                
                // Update the count of written digits
                written = (int)digits(sum[j]);
                continue;
            } 
            // If the sum of the current class label is greater than or equal to the current level, print a star
            else if (sum[j] >= i) {
                printf("%*c", padding, '*');
            } 
            // Otherwise, print a space
            else {
                printf("%*c", padding, ' ');
            }

            // Reset the count of written digits for the next class label
            written = 0;
        }
        // Move to the next line
        printf("\n");
    }

    // Print the labels for each class
    for (int j = 0; j < NUM_CLASSES; j++){
        printf("Class %d   ", j + 1); // printing the class number (adding 1 because indices start from 0)
    }
    printf("\n"); // new line for each of the 7 classLabels i see
}

float euclideanDistance(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES])
{
    /* A1.pdf: This function computes and returns the Euclidean distance between 2 arrays, each with
    16 features. Euclidean distance between two arrays v1 and v2, both of the same size
    (say N), is computed as: sqrt (v1[i] - v2[i])^2 */

    // I can start by initializing a variable to hold the sum of squares between the 2 vectors
    float sum = 0;
    // looping over each element in Num features
    int i = 0;
    while (i < NUM_FEATURES)
    {
        float difference;
        // subtracting each element in v1 and v2 in the array of features
        difference = vector1[i] - vector2[i];
        // adding the squared difference to the sum, since the formula requires the difference from v1 and v2 to do so
        sum = sum + difference * difference;
        i++;
    }

    // The last thing left to do is take the square root of the sum i just got for the E.D
    float finalEDistance;
    finalEDistance = sqrt(sum);

    // finally, we just return the distance
    return finalEDistance;
}

/* Task 5 */
int hammingDistance(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES])
{
    /* A1.pdf: Hamming distance = number of values in vector1 that differ from corresponding values in vector2 = 8
    Note that the values in vector1 that differ from corresponding values in vector2 are
    shown in red in the given example*/

    // can start by looping over the number of features (16 in each row)
    int i;
    int sum = 0; // This will hold the number of values that differ from v1 to v2
    for (i = 0; i < NUM_FEATURES; i++)
    {
        // if the elements from each vector are not equal, we increment the sum var
        if (vector1[i] != vector2[i])
        {
            sum = sum + 1;
        }
    }
    // returning the amount of vector values that are differ from each other
    return sum;
}

/* Task 6 */
float jaccardSimilarity(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES])
{
    /* Description from a1.pdf: Jaccaord simmalarity -> (number of 1 - 1 matches in vector1 - vector 2) / (number of features in vector1 or vector2 − number of 0−0 matches )
    Note that the 1-1 matches in vector1 and vector2 are shown in red in the given
    example; whereas 0-0 matches in vector1 and vector2 are shown in green. Both vector1
    and vector2 have 16 features*/

    // going to start off by looping over the number of features, its alrdy given that both have 16 features
    int j;
    int sum = 0;  // Holding the number of 1 - 1 matches
    int sum2 = 0; // holding the number of 0 - 0 matches
    for (j = 0; j < NUM_FEATURES; j++)
    {
        // while looping, if theres a 1 in vector1 and vector2, we increment sum, this is for the numerator part of the equation
        if (vector1[j] == 1 && vector2[j] == 1)
        {
            sum = sum + 1;
        }
        if (vector1[j] == 0 && vector2[j] == 0) // if both vectors have a 0-0 match, I increment sum2 
        {
            sum2 = sum2 + 1;
        }
    }
    // printf("sum: %d\n", sum);   // for testing
    // printf("sum2: %d\n", sum2); // for testing

    // To get the denominator, we subtract the number of features, by the sum2 we just found above
    int featuresSubtractedFromZeroToZeroMatches;
    featuresSubtractedFromZeroToZeroMatches = NUM_FEATURES - sum2;
    // Finally, now that i have the sum of the numerator and the denominator, we just divide them
    float resultJaccardsSimailarity;
    // if neither sum or the denominator is converted to a float, we'll get zero, so converting sum to a float is needed here lol
    resultJaccardsSimailarity = (float)sum / featuresSubtractedFromZeroToZeroMatches;
    // returning our final result
    return resultJaccardsSimailarity;
}


// https://www.geeksforgeeks.org/bubble-sort/
void bubbleSort(indexDistance arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {     
        for (j = 0; j < n-i-1; j++) { 
            if (arr[j].distance > arr[j+1].distance) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

// Defining the swap function
void swap(indexDistance* a, indexDistance* b) {
    indexDistance t = *a;
    *a = *b;
    *b = t;
}

/* Task 7 */
void findKNearestNeighbors(struct Animal dataZoo[NUM_SAMPLES], int newSample[NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors[NUM_SAMPLES])
{
    /*
    Steps of k-nearest-neighbors algorithm of ML are described below:
    1. for i = 1 to NUM_SAMPLES:
    find the distance of the new data sample with the ith data sample in zoo dataset.
    2. Sort all these distances in increaing order. Note that you need the indices of the
    data samples, so you must maintain them.
    3. Save the indices associated with the first K distances in the sorted list in
    kNearestNeighbors*/

    int i;
    // looping through the samples array
    for (i = 0; i < NUM_SAMPLES; i++)
    {
        // using the euclidean algorithm, jaccards, or hamming to find the distance with the newsample, with ith data sample in dataset
        // The distance is calculated differently depending on the chosen distance function
        if (whichDistanceFunction == 1)
        {
            idArray[i].index = i; // allows me to keep track of which samples are the nearest neighbors of the new sample.
            idArray[i].distance = euclideanDistance(newSample, dataZoo[i].features);
        }
        else if (whichDistanceFunction == 2)
        {
            idArray[i].index = i; // keeping trach of the samples that are closest to the new sample
            idArray[i].distance = hammingDistance(newSample, dataZoo[i].features); // calling distance func 2
        }
        else if (whichDistanceFunction == 3)
        {
            idArray[i].index = i; // need to keep track of the samples are the nearest neighbors of the new sample
            idArray[i].distance = jaccardSimilarity(newSample, dataZoo[i].features); // calling distance function 3
        }
    }
    // finally, just need to save the indices with the k distances in the sorted list within kNearestNeighbors
    for (i = 0; i < k; i++)
    {
        kNearestNeighbors[i] = idArray[i].index;
    }
    //Print the array after sorting
    //Print the array after sorting
    /*for (int i = 0; i < k; i++)
    {
        printf("before Index: %d, before Distance = %f\n", idArray[i].index, idArray[i].distance);
    } */

    // sorting from ascending order - big shoutout to geeksforgeeks - https://www.geeksforgeeks.org/bubble-sort/
    bubbleSort(idArray, NUM_SAMPLES);

    // Updating k nearest neighbors after sorting
    for (i = 0; i < k; i++){
        kNearestNeighbors[i] = idArray[i].index;
    }

    // Print the array after sorting
    /*for (int i = 0; i < NUM_SAMPLES; i++)
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        printf("Index: %d, Distance = %.2f\n", idArray[i].index, idArray[i].distance);
    } */
}

/* Task 8 */
int predictClass(struct Animal dataZoo[NUM_SAMPLES], int neighborsForNewSample[NUM_SAMPLES], int newSample[NUM_FEATURES], int k)
{
    /* Given the k-nearest neighbors of a new data sample, this function predicts its class and
    returns it. To do this, it assigns the most frequent class among the K neighbors as the
    predicted class for the input data sample. Note that the new sample (parameter 3) has
    NUM_FEATURE values, one for each feature*/

    // Initialize a counter for each possible class label
    int counter[NUM_SAMPLES] = {0};
    // Iterate over the k nearest neighbors
    for (int j = 0; j < k; j++){
        // Get the index of the current neighbor
        int index = neighborsForNewSample[j];

        // Get the class label of the current neighbor
        int labelCurrentNeighbor = dataZoo[index].classLabel;
        //printf("Index: %d Class label = %d\n", index, labelCurrentNeighbor); // for testing

        // Increment the count of the current class label
        counter[labelCurrentNeighbor - 1]+= 1;
    
    }
    // Initialize variables to keep track of the most frequently occurring class label
    int max = 0;
    int mostOccuredLabel = 0;

    // iterating thorugh all possible class labels
    int i = 0;
    while (i < NUM_SAMPLES){
        // If the current class label occurs more frequently than the previous most frequent label
        if (counter[i] > max){
            max = counter[i];
            mostOccuredLabel = i;
        }
        // incrementing i after each iteration
        i++;
    }

    // Return the most frequently occurring class label
    return mostOccuredLabel + 1;
}

/* Task 9 */
float findAccuracy(struct Animal dataZoo[NUM_SAMPLES], struct Animal testData[NUM_TEST_DATA], int k)
{   /* It is common in the ML world to evaluate the performance of the algorithm using
    performance measures such as accuracy. Accuracy is measured as:
    𝑎𝑐𝑐𝑢𝑟𝑎𝑐𝑦 = 𝑛𝑢𝑚𝑏𝑒𝑟 𝑜𝑓 𝑐𝑜𝑟𝑟𝑒𝑐𝑡 𝑝𝑟𝑒𝑑𝑖𝑐𝑡𝑖𝑜𝑛𝑠
    𝑡𝑜𝑡𝑎𝑙 𝑛𝑢𝑚𝑏𝑒𝑟 𝑜𝑓 𝑝𝑟𝑒𝑑𝑖𝑐𝑡𝑖𝑜𝑛𝑠
    For example, if the total number of samples (and therefore the total number of
    predictions) is 10, and the number of predictions correctly made by the ML algorithm is
    6, then the accuracy will be calculated as 60%.
    A small test dataset (with NUM_TEST_DATA samples) is given in
    a file called testData.txt. Your function must find (predict) the class of each data given
    in the testData file and use them to compute the accuracy of the k-nearest-neighbor ML
    algorithm used*/

    // initializing count to zero
    int count = 0;
    int allTheNeighbors[NUM_SAMPLES]; // array to store the indices of the k nearest neighbors for each test sample

    //printf("Number of test samples: %d\n", NUM_TEST_DATA); // testing
    // looping over the test data
    for (int i = 0; i < NUM_TEST_DATA; i++) {
        //printf("Processing test sample %d\n", i); // testing 
        // storing each actual class label here
        int realClassLabel = testData[i].classLabel;
        //printf("Real class labels: %d\n", realClassLabel); // testing
        // Calling findKNearestNeighbors with the features of the test sample
        findKNearestNeighbors(dataZoo, testData[i].features, k, 1, allTheNeighbors);

        // Calling the predictClass function to get the predicted class
        int predictedClass = predictClass(dataZoo, allTheNeighbors, testData[i].features, k);
        // printf("Predicted class for test sample %d: %d\n", i, predictedClass); // testing

        // Comparing the predicted class label with the actual class label
        if (realClassLabel == predictedClass) {
            // If they match, increment the counter for correct predictions
            count++;
        }
        printf("The number of correct predictions is %d\n", count); // testing
    }
    // Calculate the accuracy here, with the formula in the description: 𝑎𝑐𝑐𝑢𝑟𝑎𝑐𝑦 = 𝑛𝑢𝑚𝑏𝑒𝑟 𝑜𝑓 𝑐𝑜𝑟𝑟𝑒𝑐𝑡 𝑝𝑟𝑒𝑑𝑖𝑐𝑡𝑖𝑜𝑛𝑠 / 𝑡𝑜𝑡𝑎𝑙 𝑛𝑢𝑚𝑏𝑒𝑟 𝑜฿ 𝑝𝑟𝑒𝑑𝑖𝑐𝑡𝑖𝑜𝑛𝑠
    float findingAccuracy;
    // finally, dividing the number of corrrect predictions by 20 
    findingAccuracy = (float)count / NUM_TEST_DATA;
    return findingAccuracy;
}

