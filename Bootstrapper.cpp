#include <iostream>
#include <time.h> // srand; setting seeds
#include <math.h> // round
#include <algorithm> // sort

class Bootstrapper {
    private:
        int size;
        double *data;

        double mean(double *data, int num_elements) {
            int size = num_elements;
            double sum = 0;

            for (int i = 0; i < size; ++i) {
                sum += data[i];
            }

            return sum / size;
        }
        
    public:
        Bootstrapper(double *data, int num_elements) {
            this->data = data;
            this->size = num_elements;
        }

        double *mean_estimate(double *data, int iter = 1000) {
            srand(time(0)); // set random seed
            int rand_index;
            double *temp = (double*)malloc(sizeof(double)*this->size);
            double *mean_arr = (double*)malloc(sizeof(double)*iter);

            for (int j = 0; j < iter; ++j) {
                // resample data
                for (int i = 0; i < this->size; ++i) {
                    rand_index = rand() % this->size;
                    temp[i] = this->data[rand_index];
                }

                // take mean of resampled data
                mean_arr[j] = mean(temp, this->size);
            }

            // take mean of means
            double bootstrap_mean = mean(mean_arr, iter);
            std::sort(mean_arr, mean_arr+iter);

            // 2.5th percentile (approximation)
            int lower_rank = round((2.5 / 100) * iter);
            double perc_lower = (mean_arr[lower_rank] + mean_arr[lower_rank+1]) / 2;

            // 97.5th percentile (approximation)
            int upper_rank = round((97.5 / 100) * iter);
            double perc_upper = (mean_arr[upper_rank] + mean_arr[upper_rank+1]) / 2;

            // 95% confidence interval
            double *estimate_data = (double*)malloc(sizeof(double*) * 3);
            estimate_data[0] = bootstrap_mean;
            estimate_data[1] = perc_lower;
            estimate_data[2] = perc_upper;

            // free memory
            free(temp);
            free(mean_arr);

            return estimate_data;
        }

};

int main() {

    double data[] = {1.1, 1.3, 2.1, 5.0, 2.4, 6.6, 3.1, 6.2, 10.2, 4.7, 2.2, 5.5, 1.5, 7.5, 2.8, 1.1, 2.7, 7.7, 6.5, 2.5, 1.8, 9.2, 4.6};
    int size = sizeof(data)/sizeof(*data);

    Bootstrapper bs(data, size);
    double *ci = bs.mean_estimate(data);  

    std::cout << "Point estimate: " << ci[0] << std::endl;
    std::cout << "95\% confidence interval of mean: [" << ci[1] << ", " << ci[2] << "]" << std::endl;           

    free(ci);
    return 0;
}
