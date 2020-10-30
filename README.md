# BootstrapperCPP
Example implementation of a bootstrapper to estimate 95% confidence interval of the mean of sample data.

### Returns:
```c++
mean_estimate(data, iter=1000)
```

This function returns a pointer array with the 0th element being the sample estimate (bootstrapped) of the mean, 1st element being the lower bound of the confidence interval and 2nd element being the upper bound of the confidence interval.

See example below.

# How to use (example):
```c++
int main() {

    double data[] = {1.1, 1.3, 2.1, 5.0, 2.4, 6.6, 3.1, 6.2, 10.2, 4.7, 2.2, 5.5, 1.5, 7.5, 2.8, 1.1, 2.7, 7.7, 6.5, 2.5, 1.8, 9.2, 4.6};
    int size = sizeof(data)/sizeof(*data);

    Bootstrapper bs(data, size);
    double *ci = bs.mean_estimate(data);  

    std::cout << "Point estimate: " << ci[0] << std::endl;
    std::cout << "95\% confidence interval of mean: [" << ci[1] << ", " << ci[2] << "]" << std::endl;           

    return 0;
}
```

### Output:
```text
Point estimate: 4.272
95% confidence interval of mean: [3.22826, 5.37826]
```
