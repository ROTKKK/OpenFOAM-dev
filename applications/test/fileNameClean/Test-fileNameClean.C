/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2020 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    fileNameCleanTest

Description

\*---------------------------------------------------------------------------*/

#include "argList.H"
#include "fileName.H"
#include "SubList.H"
#include "IOobject.H"
#include "IOstreams.H"
#include "OSspecific.H"


using namespace Foam;

void printCleaning(fileName& filePath)
{
    Info<< "fileName = " << filePath << nl
        << "  path() = " << filePath.path() << nl
        << "  name() = " << filePath.name() << nl
        << "  joined = " << filePath.path()/filePath.name() << nl << nl;

    filePath.clean();

    Info<< "cleaned  = " << filePath << nl
        << "  path() = " << filePath.path() << nl
        << "  name() = " << filePath.name() << nl
        << "  joined = " << filePath.path()/filePath.name() << nl << nl;

    IOobject::writeDivider(Info);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Main program:

int main(int argc, char *argv[])
{
    writeInfoHeader = false;

    argList::noParallel();
    argList::validArgs.insert("fileName .. fileNameN");
    argList::addOption("istream", "file", "test Istream values");

    argList args(argc, argv, false, true);

    if (args.size() <= 1 && args.options().empty())
    {
        args.printUsage();
    }

    fileName filePath;
    if (args.optionReadIfPresent("case", filePath))
    {
        Info<< nl
            << "-case" << nl
            << "path = " << args.path() << nl
            << "root = " << args.rootPath() << nl
            << "case = " << args.caseName() << nl
            << "FOAM_CASE=" << getEnv("FOAM_CASE") << nl
            << "FOAM_CASENAME=" << getEnv("FOAM_CASENAME") << nl
            << endl;

        printCleaning(filePath);
    }

    for (label argI=1; argI < args.size(); ++argI)
    {
        filePath = args[argI];
        printCleaning(filePath);
    }

    if (args.optionFound("istream"))
    {
        args.optionLookup("istream")() >> filePath;

        Info<< nl
            << "-case" << nl
            << "path = " << args.path() << nl
            << "root = " << args.rootPath() << nl
            << "case = " << args.caseName() << nl
            << "FOAM_CASE=" << getEnv("FOAM_CASE") << nl
            << "FOAM_CASENAME=" << getEnv("FOAM_CASENAME") << nl
            << endl;

        printCleaning(filePath);
    }

    Info<< "\nEnd\n" << endl;
    return 0;
}


// ************************************************************************* //
