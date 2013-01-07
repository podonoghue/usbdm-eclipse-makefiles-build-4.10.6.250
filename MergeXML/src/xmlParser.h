/*
 * xmlParser.h
 *
 *  Created on: 22/12/2010
 *      Author: podonoghue
 */

#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMComment.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>

#include "helper-classes.h"

class XmlParser {

private:
   DualString attr_merge_actions;

   xercesc_3_1::ErrorHandler*    errHandler;

   xercesc_3_1::XercesDOMParser* mergeParser;
   xercesc_3_1::DOMDocument*     mergeDocument;

   xercesc_3_1::XercesDOMParser* patchParser;
   xercesc_3_1::DOMDocument*     patchDocument;
   static bool      verbose;

private:
   XmlParser() :
      attr_merge_actions("merge-actions"),

      errHandler(NULL),

      mergeParser(NULL),
      mergeDocument(NULL),

      patchParser(NULL),
      patchDocument(NULL)
   {
   }

   ~XmlParser() {
//      cerr << "~XmlParser()\n";
      delete mergeParser;
      delete patchParser;
      delete errHandler;
   }

private:
   typedef enum {scan, insert, replace, mergeAttrs} Actions;

   int modifyNewProjectWizardXML(xercesc_3_1::DOMElement *el);
   int modifyWizardUIXML(xercesc_3_1::DOMElement *el);
   int modifyWizardUIXMLPage(xercesc_3_1::DOMElement *el);
   int modifyWizardUIXMLCondition(xercesc_3_1::DOMNode *el);
   int addLaunchSetting( xercesc_3_1::DOMElement *el,
                         const char *conditionId,
                         const char *configurationId,
                         const char *name,
                         const char *projectType);
   int addLaunchSettings(xercesc_3_1::DOMElement *el);
   int addLaunchSettingsRefs(xercesc_3_1::DOMElement *el);
   int addLaunchSettingsRef( xercesc_3_1::DOMElement *configuration,
                             const char *id);
   int addcheckBoxItem(xercesc_3_1::DOMElement *uiElement, const char *id );

   void  load(xercesc_3_1::XercesDOMParser* &parser, xercesc_3_1::DOMDocument* &document, const char* xmlFile);
   int   mergePatchfile();
   int   openSourcefile(const char *sourcePath);
   int   openPatchfile(const char *patchPath);
   int   commit(const char* xmlFile);
   bool  mergeNodes(xercesc_3_1::DOMElement *mergeEl, xercesc_3_1::DOMElement *patchEl);
   bool  nodesMatch(xercesc_3_1::DOMElement *mergeEl, xercesc_3_1::DOMElement *patchEl);
   bool  processAttributes(xercesc_3_1::DOMElement *mergeEl, xercesc_3_1::DOMElement *patchEl);
   Actions getAction(xercesc_3_1::DOMElement *mergeEl);
   xercesc_3_1::DOMElement *removeActionAttributes(xercesc_3_1::DOMElement *patchEl);
   xercesc_3_1::DOMComment *getCommentNode(xercesc_3_1::DOMElement *element);

public:
   static int addUsbdmWizard(const char *sourcePath,
                             const char *destinationPath,
                             const char *patchPath);
};

#endif /* XMLPARSER_H_ */
