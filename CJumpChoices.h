//
// Created by chris on 4/18/18.
//

#ifndef PEGGAME_CJUMPCHOICES_H
#define PEGGAME_CJUMPCHOICES_H

struct JumpChoice{
    int from, to, jumped;
};

class CJumpChoices {
public:
    int RecCount;
    CJumpChoices() {header = NULL; RecCount = 0;};
    CJumpChoices(CJumpChoices *choices);
    void add(JumpChoice rec);
    JumpChoice get(int idx);
    void remove(int idx);
    void clear();

private:
    struct Node{
        JumpChoice *prec;
        Node *next;
    };
    Node *header;
}; // CJumpChoices

#endif //PEGGAME_CJUMPCHOICES_H
