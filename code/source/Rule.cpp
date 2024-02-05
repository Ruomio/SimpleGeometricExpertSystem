/*
 * @Author: PapillonAz 1065940593@qq.com
 * @Date: 2023-11-22 14:35:48
 * @LastEditors: PapillonAz 1065940593@qq.com
 * @LastEditTime: 2023-11-22 14:55:17
 * @FilePath: /Simple_geometric_expert_system/code/source/Rule.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AEinc
 */
#include "../include/Rule.h"

int id_count = 0;


Rule::Rule(std::vector<std::string> ant, std::string con, std::string des):id(GetId()) , antecedent(ant), consequent(con), description(des) {

}

Rule::~Rule() {

}

unsigned int Rule::GetId() {
    return id_count++;
}

std::string Rule::toString() {
    std::string str;
    str += "Rule: #" + std::to_string(id) + "\n";
    if(!this->description.empty()) {
        str += "Description: " + this->description + "\n";
    }
    str += "IF\t\t";
    for(auto s : this->antecedent) {
        str += s + "\n";
        if(s != this->antecedent.back()) {
            str  +=  "\tand\t";
        }
    }
    str += "THEN\t" + this->consequent + "\n";

    return str;
}
