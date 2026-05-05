/*********************REQUIRED HEADER FILES AND GLOBAL VARIABLES*****************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_NUM_LEN   256
#define MAX_INPUT_LEN ((MAX_NUM_LEN * 2) + 32)

char num1[MAX_NUM_LEN], num2[MAX_NUM_LEN];      // getting two numbers
char ch;                                        // getting the operator of the operation
char expression[MAX_INPUT_LEN];

/**************************PRE-REQUIRED FUNCTIONS*****************************************/

// Returns 1 if a > b, otherwise returns 0. Both numbers should not contain leading zeros.
int compare(char *a, char *b)
{
    int la = (int)strlen(a);
    int lb = (int)strlen(b);

    if (la > lb) return 1;
    if (la < lb) return 0;

    for (int index = 0; index < la; index++) {
        if (a[index] > b[index]) return 1;
        if (a[index] < b[index]) return 0;
    }

    return 0;   // equal numbers are treated as not greater
}

char* equalizeZeros(char* str, int s, int max)
{
    char* ptr = malloc((max + 1) * sizeof(char));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    memset(ptr, '0', max);
    int k = 0;
    for (int i = max - s; i < max; i++) {
        ptr[i] = str[k++];
    }
    ptr[max] = '\0';
    return ptr;
}

char* removeZeros(char *a)
{
    int N = (int)strlen(a);
    int i = 0;

    while (i < N && a[i] == '0') {
        i++;
    }

    if (i == N) {
        char *ptr = malloc(2 * sizeof(char));
        if (ptr == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        ptr[0] = '0';
        ptr[1] = '\0';
        return ptr;
    }

    char *ptr = malloc((N - i + 1) * sizeof(char));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    strcpy(ptr, a + i);
    return ptr;
}

int isValidNumber(char *a)
{
    int N = (int)strlen(a);

    if (N == 0) return 0;

    for (int i = 0; i < N; i++) {
        if (!isdigit((unsigned char)a[i])) return 0;
    }
    return 1;
}

int isZero(char *a)
{
    return (strcmp(a, "0") == 0);
}

char *add(char *a)
{
    int a1, b1;
    int N1 = (int)strlen(a);
    char* temp = malloc((N1 + 2) * sizeof(char));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    char* one = "1";
    char* allocatedOne = NULL;

    if ((int)strlen(one) != N1) {
        allocatedOne = equalizeZeros(one, 1, N1);
        one = allocatedOne;
    }

    int addArray[N1];
    int carryFlag = 0, sum, res, k = -1;

    for (int i = N1 - 1; i >= 0; i--) {
        a1 = a[i] - '0';
        b1 = one[i] - '0';
        sum = carryFlag + a1 + b1;
        res = sum % 10;
        carryFlag = sum / 10;
        addArray[++k] = res;
    }

    int j = 0;
    if (carryFlag != 0) temp[j++] = (char)(carryFlag + '0');
    while (k >= 0) temp[j++] = (char)(addArray[k--] + '0');
    temp[j] = '\0';

    if (allocatedOne != NULL) free(allocatedOne);
    return temp;
}

// Subtract b from a. Here a and b must have same length and a must be greater than/equal to b.
char *sub(char *a, char *b)
{
    int a1, b1;
    int N1 = (int)strlen(a);
    char subArray[N1];
    char* temp = malloc((N1 + 1) * sizeof(char));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int borrowFlag = 0, difference, k = -1;

    for (int i = N1 - 1; i >= 0; i--) {
        a1 = a[i] - '0';
        b1 = b[i] - '0';

        if (borrowFlag != 0) {
            a1 -= 1;
        }

        if (a1 < b1) {
            a1 += 10;
            borrowFlag = 1;
        } else {
            borrowFlag = 0;
        }

        difference = a1 - b1;
        subArray[++k] = (char)(difference + '0');
    }

    int j = 0;
    for (int i = k; i >= 0; i--) temp[j++] = subArray[i];
    temp[j] = '\0';
    return temp;
}

// Full comparison for long division.
// Returns 1 if a > b, 0 if a == b, -1 if a < b.
// This internally reuses your compare() logic after removing leading zeros.
int compareFull(char *a, char *b)
{
    char *aa = removeZeros(a);
    char *bb = removeZeros(b);
    int result;

    if (strcmp(aa, bb) == 0) {
        result = 0;
    } else if (compare(aa, bb)) {
        result = 1;
    } else {
        result = -1;
    }

    free(aa);
    free(bb);
    return result;
}

// Safe subtraction for long division.
// This reuses your equalizeZeros(), sub(), and removeZeros().
char *subtractForDivision(char *a, char *b)
{
    int lenA = (int)strlen(a);
    int lenB = (int)strlen(b);
    int maxLen = (lenA > lenB) ? lenA : lenB;

    char *paddedA = a;
    char *paddedB = b;

    if (lenA < maxLen) paddedA = equalizeZeros(a, lenA, maxLen);
    if (lenB < maxLen) paddedB = equalizeZeros(b, lenB, maxLen);

    char *rawResult = sub(paddedA, paddedB);
    char *cleanResult = removeZeros(rawResult);

    if (paddedA != a) free(paddedA);
    if (paddedB != b) free(paddedB);
    free(rawResult);

    return cleanResult;
}

char *appendDigitToRemainder(char *remainder, char digit)
{
    char *result;

    if (strcmp(remainder, "0") == 0) {
        result = malloc(2 * sizeof(char));
        if (result == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        result[0] = digit;
        result[1] = '\0';
    } else {
        int len = (int)strlen(remainder);
        result = malloc((len + 2) * sizeof(char));
        if (result == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        strcpy(result, remainder);
        result[len] = digit;
        result[len + 1] = '\0';
    }

    char *cleanResult = removeZeros(result);
    free(result);
    return cleanResult;
}

/**********************START OF OPERATIONS***************************/
void addition(char *a, char *b, char *op1, char *op2)
{
    int a1, b1;
    int N1 = (int)strlen(a);
    int addArray[N1];
    int carryFlag = 0, sum, res, k = -1;

    for (int i = N1 - 1; i >= 0; i--) {
        a1 = a[i] - '0';
        b1 = b[i] - '0';
        sum = carryFlag + a1 + b1;
        res = sum % 10;
        carryFlag = sum / 10;
        addArray[++k] = res;
    }

    printf("%s + %s = ", op1, op2);
    if (carryFlag != 0) printf("%d", carryFlag);
    while (k >= 0) {
        printf("%d", addArray[k]);
        k--;
    }
    printf("\n");
}

void subtraction(char *a, char *b, char *op1, char *op2, char ch)    // always do (a-b)
{
    int a1, b1;
    int N1 = (int)strlen(a);
    int subArray[N1];
    int borrowFlag = 0, difference, k = -1, flag = 0;

    for (int i = N1 - 1; i >= 0; i--) {
        a1 = a[i] - '0';
        b1 = b[i] - '0';

        if (borrowFlag != 0) {
            a1 -= 1;
        }

        if (a1 < b1) {
            a1 += 10;
            borrowFlag = 1;
        } else {
            borrowFlag = 0;
        }

        difference = a1 - b1;
        subArray[++k] = difference;
    }

    if (ch == '-') printf("%s - %s = -", op2, op1);
    else printf("%s - %s = ", op1, op2);

    while (k >= 0) {
        if (subArray[k] != 0 && flag == 0) {
            printf("%d", subArray[k]);
            flag = 1;
        }
        else if (flag == 1) printf("%d", subArray[k]);
        k--;
    }

    if (flag == 0) printf("0");
    printf("\n");
}

void multiplication(char *a, char *b)
{
    int N1 = (int)strlen(a);
    int N2 = (int)strlen(b);
    int k = 0;

    int *arr1 = calloc((size_t)N1, sizeof(int));
    int *arr2 = calloc((size_t)N2, sizeof(int));
    int *mulArray = calloc((size_t)(N1 + N2 + 1), sizeof(int));

    if (arr1 == NULL || arr2 == NULL || mulArray == NULL) {
        printf("Memory allocation failed\n");
        free(arr1);
        free(arr2);
        free(mulArray);
        exit(1);
    }

    for (int i = 0; i < N1; i++) arr1[i] = a[N1 - i - 1] - '0';
    for (int i = 0; i < N2; i++) arr2[i] = b[N2 - i - 1] - '0';

    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < N2; j++) {
            mulArray[i + j] += arr1[i] * arr2[j];
        }
    }

    for (int i = 0; i < N1 + N2; i++) {
        mulArray[i + 1] += mulArray[i] / 10;
        mulArray[i] %= 10;
        if (mulArray[i] != 0) k = i;
    }

    printf("%s * %s = ", a, b);
    for (int i = k; i >= 0; i--) {
        printf("%d", mulArray[i]);
    }
    printf("\n");

    free(arr1);
    free(arr2);
    free(mulArray);
}

void division(char *a, char *b, char *op1, char *op2)
{
    char *dividend = removeZeros(a);
    char *divisor = removeZeros(b);

    if (strcmp(divisor, "0") == 0) {
        printf("MATH ERROR\n");
        free(dividend);
        free(divisor);
        return;
    }

    if (compareFull(dividend, divisor) < 0) {
        printf("%s / %s = 0\nRemainder = %s\n", op1, op2, dividend);
        free(dividend);
        free(divisor);
        return;
    }

    int N = (int)strlen(dividend);
    char *quotient = malloc((N + 1) * sizeof(char));
    char *remainder = malloc(2 * sizeof(char));

    if (quotient == NULL || remainder == NULL) {
        printf("Memory allocation failed\n");
        free(dividend);
        free(divisor);
        free(quotient);
        free(remainder);
        exit(1);
    }

    remainder[0] = '0';
    remainder[1] = '\0';

    int qIndex = 0;

    for (int i = 0; i < N; i++) {
        char *newRemainder = appendDigitToRemainder(remainder, dividend[i]);
        free(remainder);
        remainder = newRemainder;

        int quotientDigit = 0;

        // In long division, this loop runs maximum 9 times for each dividend digit.
        while (compareFull(remainder, divisor) >= 0) {
            char *temp = subtractForDivision(remainder, divisor);
            free(remainder);
            remainder = temp;
            quotientDigit++;
        }

        quotient[qIndex++] = (char)(quotientDigit + '0');
    }

    quotient[qIndex] = '\0';

    char *cleanQuotient = removeZeros(quotient);
    char *cleanRemainder = removeZeros(remainder);

    printf("%s / %s = %s\nRemainder = %s\n", op1, op2, cleanQuotient, cleanRemainder);

    free(dividend);
    free(divisor);
    free(quotient);
    free(remainder);
    free(cleanQuotient);
    free(cleanRemainder);
}

int parseExpression(char *input)
{
    int i = 0, j = 0;

    num1[0] = '\0';
    num2[0] = '\0';
    ch = '\0';

    while (isspace((unsigned char)input[i])) i++;

    while (isdigit((unsigned char)input[i])) {
        if (j >= MAX_NUM_LEN - 1) return 0;
        num1[j++] = input[i++];
    }
    num1[j] = '\0';

    while (isspace((unsigned char)input[i])) i++;

    if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
        ch = input[i++];
    } else {
        return 0;
    }

    while (isspace((unsigned char)input[i])) i++;

    j = 0;
    while (isdigit((unsigned char)input[i])) {
        if (j >= MAX_NUM_LEN - 1) return 0;
        num2[j++] = input[i++];
    }
    num2[j] = '\0';

    while (isspace((unsigned char)input[i])) i++;

    if (input[i] != '\0') return 0;
    return 1;
}

/****************************MAIN FUNCTION***************************/
int main(void)
{
    char *str1, *str2, *temp1, *temp2;
    int s1, s2, max;

    while (1) {
        printf("Calc>");

        if (fgets(expression, sizeof(expression), stdin) == NULL) {
            break;
        }

        expression[strcspn(expression, "\n")] = '\0';

        if (strcmp(expression, "Exit") == 0) break;

        if (!parseExpression(expression)) {
            printf("Check your inputs!!\n");
            continue;
        }

        if (!(isValidNumber(num1) && isValidNumber(num2))) {
            printf("Check your inputs!!\n");
            continue;
        }

        str1 = removeZeros(num1);
        temp1 = str1;
        str2 = removeZeros(num2);
        temp2 = str2;

        s1 = (int)strlen(str1);
        s2 = (int)strlen(str2);
        max = (s1 > s2) ? s1 : s2;

        if ((s1 - s2) == 0) goto next;
        else if (max == s1) str2 = equalizeZeros(str2, s2, s1);
        else if (max == s2) str1 = equalizeZeros(str1, s1, s2);

next:
        if (ch == '+') {
            if (isZero(temp1)) { printf("0 + %s = %s\n", temp2, temp2); goto cleanup; }
            if (isZero(temp2)) { printf("%s + 0 = %s\n", temp1, temp1); goto cleanup; }
            addition(str1, str2, temp1, temp2);
        }
        else if (ch == '-') {
            if (strcmp(temp1, temp2) == 0) printf("%s - %s = 0\n", temp1, temp2);
            else if (compare(temp1, temp2)) subtraction(str1, str2, temp1, temp2, '+');
            else subtraction(str2, str1, temp2, temp1, '-');
        }
        else if (ch == '*') {
            if (isZero(temp1)) { printf("0 * %s = 0\n", temp2); goto cleanup; }
            if (isZero(temp2)) { printf("%s * 0 = 0\n", temp1); goto cleanup; }
            multiplication(temp1, temp2);
        }
        else if (ch == '/') {
            if (isZero(temp2)) { printf("MATH ERROR\n"); goto cleanup; }
            if (isZero(temp1)) { printf("0 / %s = 0\nRemainder = 0\n", temp2); goto cleanup; }
            division(temp1, temp2, temp1, temp2);
        }

cleanup:
        if (str1 != temp1) free(str1);
        if (str2 != temp2) free(str2);
        free(temp1);
        free(temp2);
    }

    return 0;
}
