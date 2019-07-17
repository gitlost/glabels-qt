/*  TestTextNode.cpp
 *
 *  Copyright (C) 2019  Jim Evins <evins@snaught.com>
 *
 *  This file is part of gLabels-qt.
 *
 *  gLabels-qt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  gLabels-qt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with gLabels-qt.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "TestTextNode.h"

#include "model/TextNode.h"

#include "merge/Record.h"

#include <QtDebug>


QTEST_MAIN(TestTextNode)

using namespace glabels::model;
using namespace glabels::merge;


void TestTextNode::textNode()
{
	Record record;

	TextNode textNode;
	QVERIFY( !textNode.isField() );
	QCOMPARE( textNode.data(), QString( "" ) );
	QVERIFY( textNode == TextNode() );
	QVERIFY( !(textNode != TextNode()) );
	QCOMPARE( textNode.text( nullptr ), QString( "" ) );
	QCOMPARE( textNode.text( &record ), QString( "" ) );
	QVERIFY( !textNode.isEmptyField( nullptr ) );
	QVERIFY( !textNode.isEmptyField( &record ) );

	textNode.setField( true );
	QVERIFY( textNode.isField() );
	QCOMPARE( textNode.text( &record ), QString( "" ) );
	QVERIFY( !textNode.isEmptyField( nullptr ) );
	QVERIFY( !textNode.isEmptyField( &record ) );

	textNode.setField( false );
	QVERIFY( !textNode.isField() );

	textNode.setData( QString( "data1" ) );
	QCOMPARE( textNode.data(), QString( "data1" ) );
	QCOMPARE( textNode.text( nullptr ), QString( "data1" ) );
	QCOMPARE( textNode.text( &record ), QString( "data1" ) );
	QVERIFY( !textNode.isEmptyField( nullptr ) );
	QVERIFY( !textNode.isEmptyField( &record ) );

	textNode.setField( true );
	QCOMPARE( textNode.text( nullptr ), QString( "${data1}" ) );
	QCOMPARE( textNode.text( &record ), QString( "" ) );
	QVERIFY( !textNode.isEmptyField( nullptr ) );
	QVERIFY( !textNode.isEmptyField( &record ) );

	///
	/// Constructors
	///
	TextNode textNode2( true, "data2" );
	QVERIFY( textNode2.isField() );
	QCOMPARE( textNode2.data(), QString( "data2" ) );
	textNode.setField( false );
	QVERIFY( !(textNode2 == textNode) );
	QVERIFY( textNode2 != textNode );
	textNode.setField( true );
	QVERIFY( !(textNode2 == textNode) );
	QVERIFY( textNode2 != textNode );
	textNode.setData( QString( "data2" ) );
	QVERIFY( textNode2 == textNode );
	QVERIFY( !(textNode2 != textNode) );

	///
	/// Record
	///
	record["key1"] = "";
	QCOMPARE( textNode.text( &record ), QString( "" ) );
	QVERIFY( !textNode.isEmptyField( nullptr ) );
	QVERIFY( !textNode.isEmptyField( &record ) );

	textNode.setData( QString( "key1" ) );
	QCOMPARE( textNode.text( &record ), QString( "" ) );
	QVERIFY( !textNode.isEmptyField( nullptr ) );
	QVERIFY( textNode.isEmptyField( &record ) );

	record["key1"] = "val1";
	QCOMPARE( textNode.text( &record ), QString( "val1" ) );
	QVERIFY( !textNode.isEmptyField( nullptr ) );
	QVERIFY( !textNode.isEmptyField( &record ) );
}
