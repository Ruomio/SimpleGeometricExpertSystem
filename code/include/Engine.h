/*
 * @Author: PapillonAz 1065940593@qq.com
 * @Date: 2023-11-22 15:03:27
 * @LastEditors: PapillonAz 1065940593@qq.com
 * @LastEditTime: 2023-12-01 22:06:24
 * @FilePath: /Simple_geometric_expert_system/code/include/Engine.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <fstream>
#include <iostream>
#include <regex>
#include <stack>
#include <vector>

#include "Rule.h"
#include "Handler.h"


extern std::regex re_a_rule;
extern std::regex re_if_part;
extern std::regex re_then_part;
extern std::regex re_description_part;

class Engine {
public:
    Engine() = default;
    Engine(std::vector<Rule> rule_library, std::map<std::string, ContourFact> facts_library);
    ~Engine();

    void pushConditionStack(std::string condition);
    void clearConditionStack();
    std::string  popConditionStack();
    std::string topConditionStack();
    bool isConditionStackEmpty();
    bool matchFacts(std::string ant, int contour_index);
    bool hitConsequent(std::string cons, int contour_index);
    void goal(std::string target);
    std::string run(int contour_index);
    std::string getRuleLibrary();
    std::string toString();

public:
    std::string target;
    std::vector<Rule> rule_library;
    std::map<std::string, ContourFact> facts_library;
    std::stack<std::string> condition_stack;
    std::map<std::string, std::vector<Fact>> match_facts;
    std::map<std::string, std::vector<Rule>> hit_rules;

};

/**
 * Publuc Function
*/

Rule generateRule(std::string rule);
std::vector<Rule> separateRules(std::string rules);
std::vector<Rule> readRule(std::string rule_file);
Engine setupEngine(std::string img_source);
void setGoal(Engine &e, std::string goal);
std::tuple<std::vector<std::string>, std::map<std::string, std::vector<Fact>>, std::map<std::string, std::vector<Rule>>> mainRun(Engine e);
std::vector<std::string> splitString(const std::string& input, char delimiter);

#endif