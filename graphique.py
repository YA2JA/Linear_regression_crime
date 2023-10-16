import pandas
import numpy as np
from scipy.stats import linregress
import matplotlib.pyplot as plt

def linear_regression(x, y):
    x = np.array(x)
    y = np.array(y)
    slope, intercept, r_value, p_value, std_err = linregress(x, y)
    return slope, intercept, r_value

table = pandas.read_csv("./data.csv")
x_data = table["Assault"]
y_data = table["Murder"]

slope, intercept, correlation_coefficient = linear_regression(x_data, y_data)

print("Slope (m):", slope)
print("Intercept (c):", intercept)
print("Correlation Coefficient (r):", correlation_coefficient)

plt.figure(figsize=(16, 10))

regression_line = x_data*slope + intercept
plt.scatter(x_data, y_data.where(y_data > regression_line), color='red')
plt.scatter(x_data, y_data.where(y_data < regression_line), color='green')
plt.plot(x_data, regression_line, color='red', label='Linear Regression Line')
plt.title(label="Murder / Assault", fontsize=40, color="green") 
plt.savefig("output.jpg")