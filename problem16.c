#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define countof(array) (sizeof(array) / sizeof((array)[0]))
#define MAX(left, right) ((left) > (right) ? (left) : (right))
#define MIN(left, right) ((left) < (right) ? (left) : (right))

#define TESTCASE(test_case_number, input, target, expected) \
{ \
    int actual = threeSumClosest(input, countof(input), target); \
    if (actual != expected) \
    { printf("Test %d failed: expected %d, got %d\n", test_case_number, expected, actual); } \
}

int partition(int* array, int start, int end)
{
    int pivot = array[end - 1];
    int i = start - 1;
    for (int j = start; j < end - 1; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    i++;
    int temp = array[i];
    array[i] = array[end - 1];
    array[end - 1] = temp;
    return i;
}

void quicksort(int* array, int start, int end)
{
    if (start < 0 || end - start <= 1) { return; }
    int pivot_index = partition(array, start, end);
    quicksort(array, start, pivot_index);
    quicksort(array, pivot_index + 1, end);
}

int binary_find_closest(int target, int* nums, int nums_size)
{
    int left = 0;
    int right = nums_size;
    int prev_i = 0;
    while (true)
    {
        int i = left + (right - left) / 2;
        int item = nums[i];
        if (left >= right - 1)
        {
            int current_distance = abs(target - item);
            int prev_distance = abs(target - nums[prev_i]);
            return current_distance < prev_distance ? i : prev_i;
        }
        if (item == target) { return i; }
        if (item < target)
        {
            left += (right - left) / 2;
        }
        else // item > target
        {
            right -= (right - left) / 2;
        }
        prev_i = i;
    }
}

int threeSumClosest(int* nums, int nums_size, int target)
{
    quicksort(nums, 0, nums_size);

    int closest = -1;
    int closest_distance = 1000000;
    for (int i = 0; i < nums_size; i++)
    {
        for (int j = i + 1; j < nums_size; j++)
        {
            int perfect_summand = target - nums[i] - nums[j];
            int best_summand_index = binary_find_closest(perfect_summand, nums, nums_size);
            if (best_summand_index == i || best_summand_index == j)
            {
                int best_index_2 = best_summand_index != nums_size - 1 ? best_summand_index + 1 : best_summand_index - 2;
                int best_index_3 = best_summand_index != 0 ? best_summand_index - 1 : best_summand_index + 2;
                if (best_index_2 == i || best_index_2 == j) { best_summand_index = best_index_3; }
                else if (best_index_3 == i || best_index_3 == j) { best_summand_index = best_index_2; }
                else
                {
                    best_summand_index = abs(perfect_summand - nums[best_index_2]) < abs(perfect_summand - nums[best_index_3])
                        ? best_index_2
                        : best_index_3;
                }
            }
            int sum = nums[i] + nums[j] + nums[best_summand_index];
            if (sum == target) { return sum; }
            int distance = abs(sum - target);
            if (distance < closest_distance)
            {
                closest = sum;
                closest_distance = distance;
            }
        }
    }
    return closest;
}

int main()
{
    printf("Starting...\n");
    int sample1[] = {-1,2,1,-4};
    TESTCASE(1, sample1, 1, 2)
    printf("Done\n");
}
