/*
 * @Author: PapillonAz 1065940593@qq.com
 * @Date: 2023-11-22 11:29:41
 * @LastEditors: PapillonAz 1065940593@qq.com
 * @LastEditTime: 2023-11-25 16:39:54
 * @FilePath: /Simple_geometric_expert_system/code/include/Rule.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>

extern int id_count;

class Rule {
public:
    Rule(std::vector<std::string> ant, std::string con, std::string des="");
    ~Rule();

    std::string toString();

private:
    unsigned int GetId();

public:
    unsigned int id;
    std::vector<std::string> antecedent;
    std::string consequent;
    std::string description;

};