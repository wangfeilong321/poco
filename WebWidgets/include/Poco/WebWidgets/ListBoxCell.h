//
// ListBoxCell.h
//
// $Id: //poco/Main/WebWidgets/include/Poco/WebWidgets/ListBoxCell.h#2 $
//
// Library: WebWidgets
// Package: Controls
// Module:  ListBoxCell
//
// Definition of the ListBoxCell class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef WebWidgets_ListBoxCell_INCLUDED
#define WebWidgets_ListBoxCell_INCLUDED


#include "Poco/WebWidgets/Cell.h"
#include "Poco/WebWidgets/Delegate.h"
#include "Poco/FIFOEvent.h"
#include <vector>


namespace Poco {
	namespace Net {
		class HTTPServerResponse;
	}
namespace WebWidgets {


class WebWidgets_API ListBoxCell: public Cell
	/// A Cell for a ListBox.
{
public:
	typedef Poco::AutoPtr<ListBoxCell> Ptr;

	typedef std::vector<std::pair<Any, bool> > Data; /// An element plus its selected flag
	typedef std::vector<std::string> StringData;

	static const std::string EV_LOADDATA;
	static const std::string EV_AFTERLOAD;
	static const std::string EV_ROWSELECTED;
	static const std::string ARG_SELECTED;
	static const std::string ARG_ROW;
	static const std::string VAL_SELECTED;
	static const std::string VAL_DESELECTED;

	FIFOEvent<std::pair<ListBoxCell*, Poco::Net::HTTPServerResponse*> > beforeLoad; /// thrown whenever a load is requested, internal event to which the ListBoxCellRenderer must register

	Delegate afterLoad; // thrown after data was loaded

	FIFOEvent<int> rowSelected; /// fires the row selected event

	FIFOEvent<int> rowDeselected; /// fires the row selected event

	struct WebWidgets_API RowValueChange
		/// Data sent with a rowValueChanged event. 
	{
		std::size_t row;
		const Poco::Any oldValue;
		const Poco::Any newValue;
		RowValueChange(std::size_t row, const Poco::Any& oldValue, const Poco::Any& newValue);
	};

	ListBoxCell(View* pOwner);
		/// Creates a ListBoxCell.

	Data::const_iterator begin() const;
		/// ConstIterator to all elements

	Data::iterator begin();
		/// Iterator to all elements

	Data::const_iterator end() const;
		/// ConstIterator to all elements

	Data::iterator end();
		/// Iterator to all elements

	StringData::const_iterator beginString() const;
		/// ConstIterator to all elements

	StringData::const_iterator endString() const;
		/// ConstIterator to all elements

	void setElements(const Data& elems);
		/// Initializes the combo box with the provided elements

	const Data& getElements() const;
		/// Returns all elements

	void insert(const Any& elem, bool selected = false);
		/// Add a single element to the collection, not-selected per default

	void erase(const Any& elem);
		/// Removes a single element from the collection.

	void select(const Any& elem);
		/// Selects the element.

	void deselect(const Any& elem);
		/// Deselects the element.

	void selectByIndex(int idx, bool sel = true);
		/// Selects the element by Index. idx values that are out of range are ignored

	void deselectByIndex(int idx);
		/// Deselects the element. idx values that are out of range are ignored

	void selectAll(bool sel= true);
		/// Selects all elements

	void deselectAll();
		/// Deselects all elements

	bool hasSelected() const;
		/// Returns true if at least one selected element exists

	const Any& getSelected() const;
		/// Returns the first selected element, exception if none was selected.
		/// To get all selected elements use getElements and iterate over the
		/// returned vector

	// Cell
	void handleForm(const std::string& field, const std::string& value);
	
	void handleAjaxRequest(const Poco::Net::NameValueCollection& args, Poco::Net::HTTPServerResponse& response);

	bool serializeJSON(std::ostream& out, const std::string& name);

protected:
	~ListBoxCell();
		/// Destroys the ListBoxCell.

	ListBoxCell(View* pOwner, const std::type_info& type);
		/// Creates a ListBoxCell.

	Data::iterator find(const Any& elem);
		/// Finds an element in the cell

	Data::const_iterator find(const Any& elem) const;
		/// Finds an element in the cell

private:
	Data       _data;
	StringData _fmtCache;
};


//
// inlines
//

inline ListBoxCell::Data::const_iterator ListBoxCell::begin() const
{
	return _data.begin();
}


inline ListBoxCell::Data::iterator ListBoxCell::begin()
{
	return _data.begin();
}


inline ListBoxCell::Data::const_iterator ListBoxCell::end() const
{
	return _data.end();
}


inline ListBoxCell::Data::iterator ListBoxCell::end()
{
	return _data.end();
}


inline const ListBoxCell::Data& ListBoxCell::getElements() const
{
	return _data;
}


inline void ListBoxCell::insert(const Any& elem, bool selected)
{
	_data.push_back(std::make_pair(elem, selected));
	_fmtCache.push_back(getFormatter()->format(elem));
}


inline ListBoxCell::StringData::const_iterator ListBoxCell::beginString() const
{
	return _fmtCache.begin();
}


inline ListBoxCell::StringData::const_iterator ListBoxCell::endString() const
{
	return _fmtCache.end();
}


inline void ListBoxCell::deselectByIndex(int idx)
{
	selectByIndex(idx, false);
}


inline void ListBoxCell::deselectAll()
{
	selectAll(false);
}


} } // namespace Poco::WebWidgets


#endif // WebWidgets_ListBoxCell_INCLUDED
