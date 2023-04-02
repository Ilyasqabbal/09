/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iqabbal <iqabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 00:48:00 by iqabbal           #+#    #+#             */
/*   Updated: 2023/04/02 07:16:17 by iqabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <map>

bool count_extenstion(std::string fn)
{
    int i = 0;
    int count = 0;
    while(fn[i])
    {
        if(fn[i] == '.' && ((fn[i + 1] == 'c' && fn[i + 2] == 's' && fn[i + 3] == 'v')  || (fn[i + 1] == 't' && fn[i + 2] == 'x' && fn[i + 3] == 't')))
            count++;
        i++;
    }
    if(count == 1)
        return(true);
    return(false);
}

bool file_extention(std::string fn)
{
    if((fn.substr(fn.find_last_of(".") + 1) == "csv" || fn.substr(fn.find_last_of(".") + 1) == "txt") && count_extenstion(fn) == true)
        return(true);
    return(false);
    
}
bool check_date(int year,int month,int day)
{
    if(year % 400 == 0 && month == 2 && day > 29)
        return false;
    else if ( (month == 4 || month == 6 || month == 9 || month == 11 ) && day > 30 )
        return false;
    else if(year % 400 != 0 && month == 2 && day > 28)
        return false;
    else if ( day > 31)
        return false;
    return true;
}

bool parse_date(std::string date,std::string date1)
{
    int  year;
    int  month;
    int  day;
    
   int count  = std::count(date.begin(),date.end(),'-');
   if(count != 2 && date.length() != 10)
        return false;
    if(date[4] == '-' && date[7] == '-')
    {
        year = atof((date.substr(0,date.find('-'))).c_str());
        month = atof((date.substr(date.find('-'),2)).c_str());
        day = atof((date.substr(date.rfind('-'),2)).c_str());
        if(!check_date(year,month,day))
            std::cout << "Error in date" << std::endl;
    }
    int y = atof((date1.substr(0,date1.find('-'))).c_str());
    int m = atof((date1.substr(date1.find('-'),2)).c_str());
    int d = atof((date1.substr(date1.rfind('-'),2)).c_str());
    if(year < y)
        return false;
    else if(year == y && month < m)
        return false;
    else if(year == y && month == m && day < d)
        return false;
    else
        return true;
}

bool parse_value(std::string value)
{
    long v = atof(value.c_str());
   // std::cout << v << std::endl;
    if( v < 0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        return false;
    }
    if( v > 1000)
    {
        std::cout << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}
std::multimap<std::string,double> insert_in_map()
{
    std::fstream file;
    std::string content;
    std::multimap<std::string,double>m;
    file.open("data.csv");
    if(!file)
        exit(1);
    while(!file.eof())
    {
        getline(file,content);
        int index = content.find(',');
        int len = content.find("\n") - index;
        m.insert(std::pair<std::string,double>(content.substr(0,index),atof((content.substr(index + 1,len)).c_str()))); 
    }
    return m;
}

void parse_line(std::string content,std::string date1)
{
    int i  = 0;
    int count  = std::count(content.begin(),content.end(),'|');
    if(count != 1)
        std::cout << "Error: bad input => " << content.substr(0,content.find('\0')) << std::endl;
    else
    {
        content.erase(std::remove(content.begin(), content.end(), ' '), content.end());
        std::string date = content.substr(0,content.find('|'));
        if(!parse_date(date,date1))
        {
            std::cout << "error date => " << date << std::endl;
        }
        int len = content.length() - (content.find('|') + 1 );
        std::string value = content.substr(content.find('|') + 1,len);


        // std::cout << "content " << content << std::endl;
        // std::cout << "is : " << (content.find('|') + 1 ) << std::endl;
        // std::cout << "len is : " << len << std::endl;
        // std::cout << "value : " << value << std::endl;
        
        if(parse_value(value))
        {
            std::multimap<std::string,double>m = insert_in_map();
            std::map<std::string,double>::iterator itr;
            itr = m.find(date);
            if(itr == m.end())
            {
                itr = m.lower_bound(date);
                itr--;
            }
            //if(m.find(date) == -1)
                
            //std::cout << "itr second " << itr->second << std::endl;
            std::cout << date << " => " << value << " = " << itr->second * atof(value.c_str()) << std::endl;
        }
        
    }
    
}



std::string read_file(std::string fn,std::string date1)
{
    std::fstream file;
    std::string content;
    std::string content1;
    file.open(fn);
    int i = 0;
    if(!file)
        exit(1);
    while(!file.eof())
    {
        getline(file,content1);
        int index = content1.find('|');
        int len = content1.find("\n") - index;
        if(i >= 1)
            parse_line(content1,date1);
        content += content1 + '\n';
        i++;
    }
    file.close();
    return(content);
        
}
 
std::string read_data(std::string fn)
{
    std::fstream file;
    std::string date1;
    int i;

    i = 0;
    file.open(fn);
    if(!file)
        return NULL;
    while(!file.eof())
    {
        getline(file,date1);
        if(i == 1)
            break;
        i++;
    }
    return(date1);
}
int main(int ac,char **av)
{
    std::string date1;
    if(ac == 2)
    {
        if(file_extention(av[1]))
        {
            date1 = read_data("data.csv");
            read_file(av[1],date1);
        }
    }
    else
        std::cerr<< "error argument\n";
}



//double atof (const char* str);