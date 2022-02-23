#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Function to check if an element is inside the vector or not
bool isFound(vector<int> vector, int x)
{
    for (int i = 0; i < vector.size(); i++)
    {
        if (vector[i] == x)
            return true;
    }
    return false;
}

// Finding the index of the element to be swapped out in Optimal policy
int getElementToSwapOptimal(vector<int> allocated, vector<int> stream, int start)
{
    int elementToSwapIndex, largest = -1, j;
    vector<int> maximum;
    // loop through the elements of the allocated pages
    for (int i = 0; i < allocated.size(); ++i)
    {
        // loop through the input stream from the end till the element that we want to add
        for (j = stream.size() - 1; j > start; --j)
        {
            // getting the biggest index of each element in the allocated pages
            if (allocated[i] == stream[j])
            {
                maximum.push_back(j);
                break;
            }
        }
        // if loop ends then the element is not found, which means it is the element to be replaced
        // so set its index as a high number
        if (j == start)
            maximum.push_back(stream.size() + 1);
    }
    // get maximum indix between the allocated elements to indicate which element to replace
    for (int k = 0; k < maximum.size(); ++k)
    {
        if (maximum[k] > largest)
        {
            largest = maximum[k];
            elementToSwapIndex = k;
        }
    }
    return elementToSwapIndex;
}

// Finding the index of the element to be swapped out in LRU policy
int getElementToSwapLRU(vector<int> allocated, vector<int> stream, int start)
{
    int elementToSwapIndex, smallest = 100, j;
    vector<int> minimum;
    for (int i = 0; i < allocated.size(); ++i)
    {
        // loop through the input stream from the element that we want to add till the beginning of the vector
        for (j = start; j > 0; --j)
        {
            if (allocated[i] == stream[j])
            {
                minimum.push_back(j);
                break;
            }
        }
    }
    // get minimum indix between the allocated elements to indicate which element to replace
    for (int k = 0; k < minimum.size(); ++k)
    {
        if (minimum[k] < smallest)
        {
            smallest = minimum[k];
            elementToSwapIndex = k;
        }
    }
    return elementToSwapIndex;
}

int main()
{
    int numberOfFaults = 0;
    vector<int> pageStream;
    vector<char> pageFaults;
    vector<int> allocatedPages;
    int referencedPage = 0;
    string policy;
    int numberOfPages;

    // get number of pages and policy used
    cin >> numberOfPages;
    cin >> policy;

    // scan stream of input untill input is equal to -1
    while (referencedPage != -1)
    {
        cin >> referencedPage;
        if (referencedPage == -1)
            break;
        pageStream.push_back(referencedPage);
    }

    // Otimal policy
    if (policy == "OPTIMAL")
    {
        printf("Replacement Policy = OPTIMAL\n");
        printf("-------------------------------------\n");
        printf("Page   Content of Frames\n");
        printf("----   -----------------\n");
        for (int i = 0; i < pageStream.size(); i++)
        {
            // if there is no pages allocated yet, allocate the page
            if (allocatedPages.empty())
            {
                allocatedPages.push_back(pageStream[i]);
                pageFaults.push_back(' ');
            }
            // if element already allocated no changes are made
            else if (isFound(allocatedPages, pageStream[i]))
            {
                pageFaults.push_back(' ');
            }
            // if there is allocated pages but there is still emtpy place for allocation, allocate the page
            else if (allocatedPages.size() < numberOfPages)
            {
                allocatedPages.push_back(pageStream[i]);
                pageFaults.push_back(' ');
            }
            // if replacement is needed, add page fault and apply the optimal policy from the given function and swap
            else
            {
                pageFaults.push_back('F');
                numberOfFaults++;
                int elementToSwapIndex = getElementToSwapOptimal(allocatedPages, pageStream, i);
                allocatedPages[elementToSwapIndex] = pageStream[i];
            }
            printf("%02d %c   ", pageStream[i], pageFaults[i]);
            for (int j = 0; j < allocatedPages.size(); ++j)
            {
                printf("%02d ", allocatedPages[j]);
            }
            printf("\n");
        }
    }
    // Least Recently Used policy
    else if (policy == "LRU")
    {
        printf("Replacement Policy = LRU\n");
        printf("-------------------------------------\n");
        printf("Page   Content of Frames\n");
        printf("----   -----------------\n");
        for (int i = 0; i < pageStream.size(); i++)
        {
            // if there is no pages allocated yet, allocate the page
            if (allocatedPages.empty())
            {
                allocatedPages.push_back(pageStream[i]);
                pageFaults.push_back(' ');
            }
            // if element already allocated no changes are made
            else if (isFound(allocatedPages, pageStream[i]))
            {
                pageFaults.push_back(' ');
            }
            // if there is allocated pages but there is still emtpy place for allocation, allocate the page
            else if (allocatedPages.size() < numberOfPages)
            {
                allocatedPages.push_back(pageStream[i]);
                pageFaults.push_back(' ');
            }
            // if replacement is needed, add page fault and apply the optimal policy from the given function and swap
            else
            {
                pageFaults.push_back('F');
                numberOfFaults++;
                int elementToSwapIndex = getElementToSwapLRU(allocatedPages, pageStream, i);
                allocatedPages[elementToSwapIndex] = pageStream[i];
            }
            printf("%02d %c   ", pageStream[i], pageFaults[i]);
            for (int j = 0; j < allocatedPages.size(); ++j)
            {
                printf("%02d ", allocatedPages[j]);
            }
            printf("\n");
        }
    }
    // First In First Out Policy
    else if (policy == "FIFO")
    {
        // queue is used to indicate which element is getting replaced
        queue<int> fifo;
        printf("Replacement Policy = FIFO\n");
        printf("-------------------------------------\n");
        printf("Page   Content of Frames\n");
        printf("----   -----------------\n");
        for (int i = 0; i < pageStream.size(); i++)
        {
            // if there is no pages allocated yet, allocate the page and add the element to the queue
            if (allocatedPages.empty())
            {
                fifo.push(pageStream[i]);
                allocatedPages.push_back(pageStream[i]);
                pageFaults.push_back(' ');
            }
            // if element already allocated no changes are made
            else if (isFound(allocatedPages, pageStream[i]))
            {
                pageFaults.push_back(' ');
            }
            // if there is allocated pages but there is still emtpy place for allocation, allocate the page and add the element to the queue
            else if (allocatedPages.size() < numberOfPages)
            {
                fifo.push(pageStream[i]);
                allocatedPages.push_back(pageStream[i]);
                pageFaults.push_back(' ');
            }
            // if replacement is needed
            else
            {
                pageFaults.push_back('F');
                numberOfFaults++;
                // get the first value from the queue which indicates which element to be replaced
                int value = fifo.front();
                fifo.pop();
                // find that element in the vector and replace with the wanted page
                for (int l = 0; l < allocatedPages.size(); l++)
                {
                    // when found replace and then push to the queue
                    if (allocatedPages[l] == value)
                    {
                        allocatedPages[l] = pageStream[i];
                        fifo.push(pageStream[i]);
                    }
                }
            }
            printf("%02d %c   ", pageStream[i], pageFaults[i]);
            for (int j = 0; j < allocatedPages.size(); ++j)
            {
                printf("%02d ", allocatedPages[j]);
            }
            printf("\n");
        }
    }
    else if (policy == "CLOCK")
    {
        // additional useBit vector that indicates whether each page is used or not with values 1 or 0
        // and a pointer to the current position is used
        vector<int> useBit;
        int pointer = 0;
        printf("Replacement Policy = CLOCK\n");
        printf("-------------------------------------\n");
        printf("Page   Content of Frames\n");
        printf("----   -----------------\n");
        for (int i = 0; i < pageStream.size(); i++)
        {
            // if there is no pages allocated yet, allocate the page with useBit = 1 and increment the pointer
            // the % is used to prevent the pointer from surpassing the last page index and return to the first position
            if (allocatedPages.empty())
            {
                allocatedPages.push_back(pageStream[i]);
                useBit.push_back(1);
                pointer = (pointer + 1) % numberOfPages;
                pageFaults.push_back(' ');
            }
            // if element already allocated let the useBit of the element = 1
            else if (isFound(allocatedPages, pageStream[i]))
            {
                pageFaults.push_back(' ');

                for (int l = 0; l < allocatedPages.size(); l++)
                {
                    if (allocatedPages[l] == pageStream[i])
                    {
                        useBit[l] = 1;
                    }
                }
            }
            // if there is allocated pages but there is still emtpy place for allocation
            // allocate the page with useBit = 1 and increment pointer
            else if (allocatedPages.size() < numberOfPages)
            {
                allocatedPages.push_back(pageStream[i]);
                useBit.push_back(1);
                pointer = (pointer + 1) % numberOfPages;
                pageFaults.push_back(' ');
            }
            // if replacement is needed
            else
            {
                pageFaults.push_back('F');
                numberOfFaults++;
                // loop through -maximum- the number of pages and check if the usebit is equal to 0 then replace and break
                // if the useBit is equal to 1 then set it to 0 and increment pointer untill element with useBit = 0 is found
                for (int j = 0; j <= numberOfPages; ++j)
                {
                    if (useBit[pointer] == 0)
                    {
                        allocatedPages[pointer] = pageStream[i];
                        useBit[pointer] = 1;
                        pointer = (pointer + 1) % numberOfPages;
                        break;
                    }
                    useBit[pointer] = 0;
                    pointer = (pointer + 1) % numberOfPages;
                }
            }
            printf("%02d %c   ", pageStream[i], pageFaults[i]);
            for (int j = 0; j < allocatedPages.size(); ++j)
            {
                printf("%02d ", allocatedPages[j]);
            }
            printf("\n");
        }
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", numberOfFaults);
    return 0;
}
