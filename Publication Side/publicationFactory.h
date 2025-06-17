/*
-----------------------------------------------------------------------------
 File: publicationFactory.h
 Description: Factory class for creating Publication derived media types.
              Implements Factory design pattern to create appropriate
              publication objects based on type codes.
 Author: Sharjeel Khan
 Assumptions: Type codes 'F', 'C', 'P' map to Fiction, Children, Periodical
              Invalid type codes should be handled gracefully
 -----------------------------------------------------------------------------
*/

#ifndef PUBLICATION_FACTORY_H
#define PUBLICATION_FACTORY_H

#include "media.h"
#include "fiction.h"
#include "children.h"
#include "periodical.h"
#include <iostream>

class PublicationFactory {
public:

    // Creates factory object ready to create publications
    PublicationFactory() = default;
 
    // Cleans up factory resources
    ~PublicationFactory() = default;


    // Creates new Media object based on publication type code
    Media* createPublication(char type) const;
};

#endif // PUBLICATION_FACTORY_H