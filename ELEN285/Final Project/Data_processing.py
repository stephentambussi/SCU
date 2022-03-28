#ELEN 285 Final Project
#For Site 690
from math import floor
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df_og = pd.read_csv(r"C:\Users\steve\Desktop\ELEN285\Final Project\csv\690.csv") #unmodified dataframe
df = df_og.drop(df_og[df_og['value'] == 0].index) #remove all rows with error values (0 kWh)

#Numpy arrays of each column in the csv
np_timestamp = df.loc[:,'timestamp'].values #timestamp value
np_datetime = df.loc[:,'dttm_utc'].values #yyyy-mm-dd and 24-hour time
np_powervalue = df.loc[:,'value'].values #power reading of site in kWh
np_estimated = df.loc[:,'estimated'].values #boolean (0 | 1) if reading was estimated
np_anomaly = df.loc[:,'anomaly'].values #non-blank value if reading was erroneous

# Chart for load on weekdays vs weekends
df_datetime = pd.to_datetime(df['dttm_utc']) 
df_days_of_week = df_datetime.dt.weekday #0-6 for Mon-Sun
df_month = df_datetime.dt.month # returns month of value January (1) - December (12)
np_days_of_week = df_days_of_week.values #convert to np_array
np_month = df_month.values #convert to np_array

np_load_weekends = np.array([]) #Sat(5) & Sun(6)
np_load_weekdays = np.array([]) #Mon(0), Tues(1), Wed(2), Thu(3), Fri(4)

idx = 0 #index var

#Get load on weekends and weekdays 
for day in np_days_of_week:
    if day > 4:
        np_load_weekends = np.append(np_load_weekends, np_powervalue[idx])
        np_load_weekdays = np.append(np_load_weekdays, np.nan) #equalize values for graph
    else:
        np_load_weekdays = np.append(np_load_weekdays, np_powervalue[idx])
        np_load_weekends = np.append(np_load_weekends, np.nan)
    idx = idx + 1

#Display x-axis ticks in values of first of each month (1-12)
ir = 1 #ignore first value of array (first of month)
while ir < np_month.size:
    comparison_val = 0
    if ir+1 < np_month.size: #prevent out-of-bounds
        comparison_val = np_month[ir+1]
    if np_month[ir] == comparison_val:
        np_month[ir] = 0 #set to zero value (null representation)
    elif np_month[ir] != comparison_val: #case where transition between month
        np_month[ir] = 0
        ir += 1 #skip first of each month
    ir += 1
np_month[np_month.size - 1] = 0 #ignore last value (month turnover to next year)

# x_t = range(len(np_month))
# plt.plot(x_t, np_load_weekdays, label="Power Load of Site during Weekdays")
# plt.plot(x_t, np_load_weekends, label="Power Load of Site during Weekends")
# plt.title("Site 690 Power Load Weekdays vs Weekends")
# plt.ylabel("Power Reading (kW/h)")
# plt.xlabel("Months of the Year (2012-2013)")
# plt.legend()
# plt.xticks(x_t, np_month) 

# #improve appearance of x-axis labels
# xt2 = plt.gca().xaxis.get_major_ticks() 
# for i in range(len(xt2)):
#     if np_month[i] == 0:
#         xt2[i].set_visible(False)

# plt.show()

#General load graph of all data points throughout the year
maxload = np.amax(np_powervalue)
minload = np.amin(np_powervalue)
max_load_idx = np.where(np_powervalue == maxload) #get index of max load in array
max_load_idx = int(max_load_idx[0])
min_load_idx = np.where(np_powervalue == minload) #get index of min load in array
min_load_idx = min_load_idx[0] #particular to my data: convert from tuple to array
min_load_idx = min_load_idx[0] #particular to my data: convert from array to scalar
max_load_formatted = "{:.2f}".format(maxload)
min_load_formatted = "{:.2f}".format(minload)
max_load_label = "Max Load = " + max_load_formatted + " (kW/h)"
min_load_label = "Min Load = " + min_load_formatted + " (kW/h)"

# x_t = range(len(np_month))
# plt.plot(x_t, np_powervalue, label="Power Load of Site Every Day of Year")
# plt.annotate(max_load_label, (max_load_idx, maxload), textcoords="offset points", xytext=(0, 5), ha="center")
# plt.annotate(min_load_label, (min_load_idx, minload), textcoords="offset points", xytext=(0, -5), ha="center")
# plt.title("Site 690 Power Load through 2012-2013")
# plt.ylabel("Power Reading (kW/h)")
# plt.xlabel("Months of the Year (2012-2013)")
# plt.legend()
# plt.xticks(x_t, np_month)

# #improve appearance of x-axis labels
# xt2 = plt.gca().xaxis.get_major_ticks() 
# for i in range(len(xt2)):
#     if np_month[i] == 0:
#         xt2[i].set_visible(False)

# plt.show()


#Very ugly and large algorithm to calculate CBL (Customer Baseline Load) ... but it works
def CBL_calculator(eligible_days, dr_event_times):
    #eligible_days is an array of strings: 10 eligible days for CBL calculation in yyyy-mm-dd format
    #dr_event_times is an array of ints: these are the hours in 24 hr time that the dr event occurred
    days_powervalues = np.zeros(shape=(10, 288)) #10 rows, 288 columns
    avg_event_period_usage = np.zeros(10) #kW/h
    total_event_period_usage = np.zeros(10) #kW
    five_highest_days_indices = np.zeros(5) #holds the indices of the 5 highest usage days in days_powervalues
    # [highest day index, ... , fifth highest day index]
    avg_day_cbl = np.zeros(288) #final result
    iter1 = 0
    for day in eligible_days:
        iter2 = 0
        iter3 = 0
        #get values for each day
        for val in np_datetime:
            if(val.startswith(day)):
                days_powervalues[iter1][iter2] = np_powervalue[iter3]
                iter2 = iter2 + 1
            iter3 = iter3 + 1
        #calculate avg_event_period_usage and total_event_period_usage for dr event times
        total_total_usage = 0
        total_total_cnt = 0
        for hr in dr_event_times:
            total_usage = 0
            total_cnt = 0
            five_min_counter = 0
            for i in range(288): #go through each col of matrix (whole day)
                if(floor(five_min_counter / 60) == hr):
                    total_usage += days_powervalues[iter1][i]
                    total_cnt += 1
                five_min_counter = five_min_counter + 5

            total_total_usage += total_usage
            total_total_cnt += total_cnt
        avg_event_day_usage = total_total_usage / total_total_cnt
        total_event_day_usage = avg_event_day_usage * len(dr_event_times)
        avg_event_period_usage[iter1] = avg_event_day_usage
        total_event_period_usage[iter1] = total_event_day_usage

        iter1 = iter1 + 1
    #get indices of 5 highest usage days
    for i in range(5):
        max = total_event_period_usage[i]
        max_idx = 0
        for j in range(10):
            if(total_event_period_usage[j] > max and i != j):
                max = total_event_period_usage[j]
                max_idx = j
        total_event_period_usage[max_idx] = 0
        five_highest_days_indices[i] = max_idx
    
    five_highest_days_indices = five_highest_days_indices.astype(int)
    #calculate final result
    for x in range(avg_day_cbl.size): #for each column
        total = 0
        for y in range(five_highest_days_indices.size): #for each selected row
            total += days_powervalues[five_highest_days_indices[y]][x]
        avg_day_cbl[x] = total / 5
    
    return avg_day_cbl


#DR event (6/21/2012) load graph and baseline (CBL)
# days should be in descending order 
days = ["2012-06-18", "2012-06-15", "2012-06-14", "2012-06-13", "2012-06-12",
        "2012-06-11", "2012-06-08", "2012-06-07", "2012-06-06", "2012-06-05"]
event_times = [13, 14, 15, 16, 17] #DR event from 13:00 to 18:00
dr_event_day_cbl = CBL_calculator(days, event_times)
np_dr_event_day_powervalues = np.array([])
np_dr_event_times = np.array([])

#Get actual power values from day of dr event and hr values (for x-axis tick labels)
idx2 = 0
dr_day = "2012-06-21"
for val in np_datetime:
    if(np_datetime[idx2].startswith(dr_day)):
        np_dr_event_day_powervalues = np.append(np_dr_event_day_powervalues, np_powervalue[idx2])
        temp_str = val.split()
        temp_str = temp_str[1] 
        #truncate string to remove seconds
        np_dr_event_times = np.append(np_dr_event_times, temp_str[0:5])
    idx2 = idx2 + 1

x_ticks = range(len(np_dr_event_times))
plt.plot(x_ticks, np_dr_event_day_powervalues, label="Power Load of Site during DR Day")
plt.plot(x_ticks, dr_event_day_cbl, label="Customer Baseline Load (CBL) during DR Day")
plt.title("Site 690 Power Load during DR Event: June 21st, 2012")
plt.ylabel("Power Reading (kW/h)")
plt.xlabel("Time")
plt.xticks(x_ticks, np_dr_event_times, rotation=45) #set x-axis values to time intervals

#improve appearance of x-axis labels
xticks2 = plt.gca().xaxis.get_major_ticks() 
for i in range(len(xticks2)):
    if i % 12 != 0:
        xticks2[i].set_visible(False)

#Add highlighted x-span to show DR event activation
plt.axvspan(156, 216, color='red', alpha=0.25, label="DR Event Activation")
plt.legend()
plt.show()

#Min and max load of site
max_load = np.amax(np_powervalue)
max_load_str = "Max Load of Site = " + str(max_load) + " kW/h"
print(max_load_str)
min_load = np.amin(np_powervalue)
min_load_str = "Min Load of Site = " + str(min_load) + " kW/h"
print(min_load_str)

#Percentage of missing values (the error values)
num_rows_df_og = df_og.shape[0]
num_rows_df = df.shape[0]
percentage = (1 - (num_rows_df / num_rows_df_og)) * 100
percent_formatted = "{:.4f}".format(percentage)
percentage_str = "Percentage of missing data points = " + percent_formatted + "%"
print(percentage_str)