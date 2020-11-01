#include <stdio.h>
int main()
{
    int i;
    int n;
    int k = 0;
    printf("Enter n = ");
    scanf("%d", &n);
    for (i = 2; i < n; i = i + 1)
    {
        if ((n % i) == 0)
        {
            k = k + 1;
            break;
        }
    }
    if (k != 0)
        printf("Khong la so nguyen to=%d ", i);
    else
        printf("La so nguyen to = %d\n", i);
}
