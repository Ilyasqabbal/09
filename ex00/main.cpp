/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iqabbal <iqabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 00:48:00 by iqabbal           #+#    #+#             */
/*   Updated: 2023/03/27 03:07:25 by iqabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

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

std::string read_file(std::string fn)
{
    std::fstream file;
    std::string content;
    std::string content1;
    file.open(fn);
    if(!file)
        return NULL;
    while(!file.eof())
    {
        getline(file,content1);
        content += content1 + '\n';
    }
    std::cout << content << std::endl;
    file.close();
    return(content);
        
}
int main(int ac,char **av)
{
    if(ac == 2)
    {
        if(file_extention(av[1]))
        {
            read_file(av[1]);
        }
            
    }
    else
    {
        std::cerr<< "error argument\n";
    }
}