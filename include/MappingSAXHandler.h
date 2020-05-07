/*
 * MappingSAXHandler.h
 *
 *  Created on: May 4, 2020
 *      Author: roseba
 */

#ifndef SRC_MAPPINGSAXHANDLER_H_
#define SRC_MAPPINGSAXHANDLER_H_
#include <iostream>
#include <xercesc/sax/HandlerBase.hpp>

class MappingSAXHandler: public xercesc::HandlerBase {
public:
    ~MappingSAXHandler();
    MappingSAXHandler();
    void startElement(const XMLCh *name, xercesc::AttributeList &attrs) override;
    void fatalError(const xercesc::SAXParseException &exc) override;
};

#endif /* SRC_MAPPINGSAXHANDLER_H_ */
