#ifndef PARSER_H
#define PARSER_H


class Parser : public QXmlDefaultHandler
{
public:
    Parser();

    bool startDocument();

    bool startElement();



};

#endif // PARSER_H
