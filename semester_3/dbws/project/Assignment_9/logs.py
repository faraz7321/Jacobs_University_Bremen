import re
import os
import csv
import time

# Nov 12

def format_date(raw_date):
    
    date_conversion_dict={"Jan":"01","Feb":"02", "Mar":"03", "Apr":"04", "May":"05", "Jun":"06", "Jul":"07", "Aug":"08", "Sep":"09", "Oct":"10", "Nov":"11", "Dec":"12"}
    new_date = raw_date[0:2] +"."  + date_conversion_dict[raw_date[3:6]]+ "."+ raw_date[7:11]
    # print(new_date)  
    return new_date     
   
    

def main():
    access_log_file_name ="all_access.txt"
    try:
        username = input("Enter your clamv user name to be used to login to get access log: ")
        command_str = "scp "+username+"@10.72.1.14:/var/log/apache2/access_log ./"
        os.system(command_str)
        access_log_file_name = "access_log"
    except:
        print("Errror while sshing into clamv .")
        print("Error while fetching data")
        # print("Accessing the file, all_access.txt, as default")
        time.sleep(2)
        exit()
        
        
    print(access_log_file_name, "is the filename")
    
    reading_file_pointer = open(access_log_file_name, 'r')
    csv_file_pointer = open('access_result.csv', 'w')
    writer = csv.writer(csv_file_pointer)
    header = ['IP', 'Date', 'Time', 'Browser and OS', 'Request string']
    writer.writerow(header)
    
    
    count = 0
    page_array = []
    count_my_visit = 0
    while True:
        count += 1
        line = reading_file_pointer.readline()
        print(line)
        if not line:
            break
        
        if '~murajput' in line and '200' in line and 'internal dummy connection' not in line:
            csv_row =[]
            count_my_visit += 1
            
            # IP
            # print(re.findall(r'\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}', line)[0])
            csv_row.append(re.findall(r'\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}', line)[0])
            
            
            # date
            # print(re.search('\[(.*?)\:', line).group(1))
            formatted_date = format_date(re.search('\[(.*?)\:', line).group(1))
            print(formatted_date)
            csv_row.append(formatted_date)
            
            
            # Time
            # print(re.findall(r'\d{2}\:\d{2}\:\d{2}', line)[0])
            csv_row.append(re.findall(r'\d{2}\:\d{2}\:\d{2}', line)[0])
            
            
            # browser but try block because sometime browser detail is not there
            try:
                # print(re.search('\" \"(.*?)\"', line).group(1)) 
                csv_row.append(re.search('\" \"(.*?)\"', line).group(1))
            except:
                # print("--N/A data not there--")
                csv_row.append('--N/A data not there--')
            
            # page array
            if (re.findall(r'\w{4,50}\.php', line)[0]) not in page_array:
                page_array.append((re.findall(r'\w{4,50}\.php', line)[0]) )
                
            # Request type  
            # print(re.search('[A-Z]{2,5}(.*?)\"', line).group(1))
            csv_row.append(re.search('[A-Z]{2,5}(.*?)\"', line).group(1))
            # print(csv_row)
            # print("============")
            writer.writerow(csv_row)
                
    # print(page_array,"------")
    reading_file_pointer.close()
    csv_file_pointer.close()
    print("the number of line for my visit is ", count_my_visit)

if __name__ == "__main__":
    main()