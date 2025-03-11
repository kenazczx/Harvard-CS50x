#include <cs50.h>
#include <stdio.h>

int count_digits(long number);
int get_first_digits(long number, int digits);
bool check_luhn(long number);

int main(void)
{
    // Get user input
    long number = get_long("Number: ");

    // Step 1: Validate using Luhn’s Algorithm
    if (!check_luhn(number))
    {
        printf("INVALID\n");
        return 0;
    }

    // Step 2: Extract important details
    int digits = count_digits(number);
    int first_one = get_first_digits(number, 1);
    int first_two = get_first_digits(number, 2);

    // Step 3: Determine card type
    if (digits == 15 && (first_two == 34 || first_two == 37))
    {
        printf("AMEX\n");
    }
    else if ((digits == 13 || digits == 16) && first_one == 4)
    {
        printf("VISA\n");
    }
    else if (digits == 16 && (first_two >= 51 && first_two <= 55))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Function to validate Luhn's Algorithm
bool check_luhn(long number)
{
    int sum = 0;
    bool alternate = false;

    while (number > 0)
    {
        int digit = number % 10;

        if (alternate)
        {
            digit *= 2;
            if (digit > 9) // Sum of digits if doubled value > 9
            {
                digit = (digit % 10) + (digit / 10);
            }
        }

        sum += digit;
        alternate = !alternate;
        number /= 10;
    }

    return (sum % 10 == 0);
}

// Function to count number of digits
int count_digits(long number)
{
    int count = 0;
    while (number > 0)
    {
        count++;
        number /= 10;
    }
    return count;
}

// Function to extract the first N digits
int get_first_digits(long number, int digits)
{
    while (count_digits(number) > digits) // Reduce until only 'digits' remain
    {
        number /= 10;
    }
    return number;
}
