#include <iostream>
#include <vector>
#include <cmath>
#include "csv.hpp"

using namespace csv;

// Create a CSVReader object with the path to your CSV file
CSVReader reader("data.csv");

int colmn_size;
int row_size;

double square(double a);
void load_data(std::vector<std::vector<double>> *data);
void smaller_square_coef(std::vector<std::vector<double>> *data, int pos[], double *ptr_coef[]);
void calculate_r(std::vector<std::vector<double>> *data, int pos[], double *ptr_coef);
void select(int * selection_array);

const bool DEBUG = true;

int main()
{
    int n = 6;
    double coef_a, coef_b, coef_r;
    int colmns[2];
    std::vector<std::vector<double>> data = {};
    load_data(&data);
    printf("data size ( %d x %d ) \n\n", row_size, colmn_size);
    
    try
    {
        select(colmns);
        smaller_square_coef(&data, colmns, {&coef_a, &coef_b, &coef_r});
        printf("\n\ncoef a: %f coef b: %f coef r: %f%% \n\n\n", coef_a, coef_b, coef_r*100);
    }
    catch (int n) {
        for (auto i :{0,1,3})
        {
            for (auto j :{1, 2, 3})
            {
                if (i==j || i==3 && j==1) continue;
                printf("%d - %d", i, j);
                colmns[0] = i;
                colmns[1] = j;
                smaller_square_coef(&data, colmns, ptr_coef);
                printf("\ncoef a: %f coef b: %f coef r: %f%% \n", coef_a, coef_b, coef_r*100);
            }
        }
    }
    return 0;
}


void select(int *selection_array) {
    int input;

    //
    printf("Select an option:\n");
    printf("0. murder and assault correlation\n");
    printf("1. murder and UrbanPop correlation \n");
    printf("2. murder and Rape correlation\n");
    printf("3. assault and UrbanPop correlation\n");
    printf("4. assault and Rape correlation\n");
    printf("5. Rape and UrbanPop correlation \n\n");
    printf("Enter your choice (0-5): ");
    scanf("%d", &input);
    //

    switch (input) {
        case 0:
            selection_array[0] = 0;
            selection_array[1] = 1;
            break;
        case 1:
            selection_array[0] = 0;
            selection_array[1] = 2;
            break;
        case 2:
            selection_array[0] = 0;
            selection_array[1] = 3;
            break;
        case 3:
            selection_array[0] = 1;
            selection_array[1] = 2;
            break;
        case 4:
            selection_array[0] = 1;
            selection_array[1] = 3;
            break;
        case 5:
            selection_array[0] = 2;
            selection_array[1] = 3;
            break;
        default:
            printf("Invalid choice\n");
            throw (6);
    }
}


void load_data(std::vector<std::vector<double>> *data)
{
    for (auto& row: reader)
    {
       std::vector<double> line = {
            row["Murder"].get<double>(),
            row["Assault"].get<double>(), 
            row["UrbanPop"].get<double>(), 
            row["Rape"].get<double>()
        };
        (*data).push_back(line);
    }
    colmn_size = (*data).size();
    row_size = (*data)[0].size(); 
}

void smaller_square_coef(std::vector<std::vector<double>> *data, int pos[], double *ptr_coef[])
{   

    double x = 0;
    double y = 0;

    double x_square = 0;
    double y_square = 0;

    double xy = 0;

    for (auto row: *data)
    {
        x+= row[pos[0]];
        y+= row[pos[1]];

        x_square+= square(row[pos[0]]);
        y_square+= square(row[pos[1]]);

        xy += row[pos[0]] * row[pos[1]];
    }

    double x_mean = x / colmn_size;
    double y_mean = y / colmn_size;

    double xy_mean = (xy) / colmn_size;

    double x_square_mean = x_square / colmn_size;
    double x_mean_square = square(x_mean);

    double y_square_mean = y_square / colmn_size;
    double y_mean_square = square(y_mean);

    double conv_xy = (xy_mean) - (x_mean * y_mean);
    if (DEBUG) 
    {
        printf("x total : %f\n", x);
        printf("y total : %f\n", y);

        printf("x mean : %f\n", x_mean);
        printf("y mean : %f\n", y_mean);
        printf("xy mean : %f\n", xy_mean);
        
        printf("x square mean : %f\n", x_square_mean);
        printf("x mean square : %f\n", x_mean_square);
        
        printf("y square mean : %f\n", y_square_mean);
        printf("y mean square : %f\n", y_mean_square);
    }

    *ptr_coef[0] =  conv_xy / (x_square_mean - x_mean_square);
    *ptr_coef[1] =  (y_mean) - *ptr_coef[0] * x_mean;
    *ptr_coef[2] =  conv_xy / ( std::sqrt(x_square_mean - x_mean_square) * std::sqrt(y_square_mean - y_mean_square));
}

double square(double a)
{
    return  a * a;
}