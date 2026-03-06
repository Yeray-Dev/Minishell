void free_dblptr(char **ptr)
{
    int i = 0;

    if (!ptr)
        return;
    while (ptr[i])
    {
        free(ptr[i]);
        i++;
    }
    free(ptr);
}

static char *ft_strjoin3(const char *a, const char *b, const char *c)
{
    char *res;
    size_t len_a = ft_strlen(a);
    size_t len_b = ft_strlen(b);
    size_t len_c = ft_strlen(c);
    size_t i = 0, j;

    res = malloc(len_a + len_b + len_c + 1);
    if (!res)
        return NULL;

    j = 0;
    while (i < len_a)
        res[j++] = a[i++];
    i = 0;
    while (i < len_b)
        res[j++] = b[i++];
    i = 0;
    while (i < len_c)
        res[j++] = c[i++];
    res[j] = '\0';
    return res;
}



static long long atoi_overflow_core(const char *str, int *error, int sign)
{
    long long result = 0;
    int i = 0;

    while (str[i] >= '0' && str[i] <= '9')
    {
        long long digit = str[i] - '0';
        if (sign == 1 && result > (LLONG_MAX - digit) / 10)
        {
            *error = 1;
            return 0;
        }
        if (sign == -1 && -result < (LLONG_MIN + digit) / 10)
        {
            *error = 1;
            return 0;
        }
        result = result * 10 + digit;
        i++;
    }
    if (str[i] != '\0')
    {
        *error = 1;
        return 0;
    }
    return result * sign;
}

long long atoi_overflow(const char *str, int *error)
{
    int sign = 1;
    int i = 0;

    if (error)
        *error = 0;
    if (!str)
    {
        if (error)
            *error = 1;
        return 0;
    }
    while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    if (str[i] < '0' || str[i] > '9')
    {
        if (error)
            *error = 1;
        return 0;
    }
    return atoi_overflow_core(&str[i], error, sign);
}
