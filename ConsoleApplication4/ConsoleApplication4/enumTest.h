#pragma once

#include <iostream>
#include <string>
#include <memory>

using namespace std;
using std::string;

class GeneralChannelRule {

public:
    virtual void process() {
        cout << "GeneralChannelRule process." << endl;
    };

};

class TouTiaoChannelRule : public GeneralChannelRule {


public :
    TouTiaoChannelRule() {
        cout << "TouTiaoChannelRule constructor." << endl;
    }

    void process() {
        cout << "TouTiaoChannelRule process." << endl;
    }
};

class TencentChannelRule : public GeneralChannelRule {

public:
    TencentChannelRule() {
        cout << "TencentChannelRule constructor." << endl;
    }

    void process() {
        cout << "TencentChannelRule process." << endl;
    }
};


inline void Test_Enum()
{
    shared_ptr<GeneralChannelRule> rule = make_shared<GeneralChannelRule>();
    rule->process();

    shared_ptr<GeneralChannelRule> rule1 = make_shared<TouTiaoChannelRule>();
    rule1->process();

    shared_ptr<GeneralChannelRule> rule2 = make_shared<TencentChannelRule>();
    rule2->process();

}
