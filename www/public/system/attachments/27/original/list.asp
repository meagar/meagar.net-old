<%

'
' Used internally by the mne_List class to stored nodes in the linked list
'

class mne_ListNode
	public next_ ' "pointer" next node in the list
	public prev_ ' "pointer" previous node in the list
	public value ' "pointer" to the nodes current value
	
	public sub Class_Initialize
		next_ = null
		prev_ = null
		value = null
	end sub
end class

class mne_ListIterator
	public pos_ ' "pointer" to a mne_ListNode
	public end_ ' "pointer" to a mne_ListNode signifying end-of-list
	public reverse_ ' Whether or not this is a reverse iterator

	private sub Class_Initialize
		pos_ = null
		end_ = null
	end sub

	public sub Init(pos, endPos)
		set pos_ = pos
		set end_ = endPos
	end sub

	public function moveNext()
		if reverse_ then
			set pos_ = pos_.prev_
		else
			set pos_ = pos_.next_
		end if
		moveNext = not finished
	end function

	public function finished
		finished = pos_ is end_
	end function

	public default property get Value
		if isObject(pos_.Value) then
			set Value = pos_.Value	
		else
			Value = pos_.Value
		end if
	end property
end class

' A linked-list, closely following the interface of C++'s std::list, if not
' the implimentation
class mne_List
	public sub Class_Initialize
		set head_ = makeNode_("head", null, null)
		set tail_ = makeNode_("end", null, null)
		set head_.next_ = tail_
		set tail_.prev_ = head_
	end sub

	' Return the number of elements in the list
	public property get Count
		count = 0
		dim n : set n = head_
		while not n.next_ is tail_
			count = count + 1
			set n = n.next_
		wend
	end property

	' Return true if the list is empty, false otherwise
	public function isEmpty()
		isEmpty = (count = 0)
	end function

	' Convert the list to a standard vbscript array
	public function toArray()
		redim r(count() - 1)
		dim j : j = 0

		dim i : set i = new mne_ListIterator
		i.init head_, tail_

		while i.moveNext
			if isObject(i()) then
				set r(j) = i()
			else
				r(j) = i()
			end if
			j = j + 1
		wend
		toArray = r
	end function

	'
	' Random access operations
	'

	
	' Clear the list
	public function clear()
		set head_.next_ = tail_
		set tail_.prev_ = head_
	end function

	' Return the n'th item in the list
	public default property get at(index)
		dim idx : idx = clng(index)
		mne_assert idx >= 0 and idx < count(), "Idx out of range"
		dim b : set b = begin
		while idx > 0
			b.moveNext
			idx = idx - 1 
		wend
		if isObject(b.value) then
			set At = b.value
		else
			At = b.value
		end if
	end property

	' Set a value at a given index (non-object types)
	public property let at(index, value)
		dim i : set i = makeItr_(index)
		i.pos_.value = value
	end property

	' Set a value at a given index (object types)
	public property set at(index, value)
		dim i
		if not isObject(index) then
			set i = makeItr_(index)
		else
			set i = index
		end if
		set i.value = value
	end property

	' Insert the given value after the given iterator
	public sub insert(value, itr)
		dim n
		dim pos : set pos = itr.pos_
		if itr.reverse_ then
			' Reverse iterator - insert before
			set n = makeNode_(value, pos.prev_, pos)
			set pos.prev_.next_ = n
			set pos.prev_ = n
		else
			' Forward iterator - insert after
			set n = makeNode_(value, pos, pos.next_)
			set pos.next_.prev_ = n
			set pos.next_ = n
		end if
	end sub

	' Insert the value before the given iterator
	public sub insert_before(value, itr)
		dim n
		dim pos : set pos = itr.pos_
		if itr.reverse_ then
			' Referse iterator - insert after
			set n = makeNode_(value, pos, pos.next_)
			set pos.next_.prev_ = n
			set pos.next_ = n
		else
			' Forward iterator - insert before
			set n = makeNode_(value, pos.prev_, pos)
			set pos.prev_.next_ = n
			set pos.prev_ = n
		end if
	end sub
	
	' Remove the value at itr
	public sub Remove(itr)
		dim i : set i = makeItr_(itr)

		' It's an iterator
		dim pos : set pos = i.pos_
		mne_assert not pos is tail_, "Cannot remove end"
		mne_assert not pos is head_, "Cannot remove rend"

		set pos.next_.prev_ = pos.prev_
		set pos.prev_.next_ = pos.next_
		i.pos_ = null
	end sub

	' Erase from itrFirst up to, but not including itrLast
	public sub erase(itrFirst, itrLast)
		mne_assert itrFirst.reverse_ = itrLast.reverse_ _
			, "Cannot mix reverse/forward iterators"
			
		dim pos1 : set pos1 = itrFirst.pos_
		dim pos2 : set pos2 = itrLast.pos_
		
		if itrFirst.reverse_ then
			set pos1.next_.prev_ = pos2
			set pos2.next_ = pos1.next_
		else
			set pos1.prev_.next_ = pos2
			set pos2.prev_ = pos1.prev_
		end if
	end sub
	
	' Swap the values at two locations
	public function swap(idx1, idx2)
		dim i1 : set i1 = makeItr_(idx1)
		dim i2 : set i2 = makeItr_(idx2)
		dim tmp
		if isObject(i1.pos_.value) then
			set tmp = i1.pos_.value
			if isObject(i2.pos_.value) then
				set i1.pos_.value = i2.pos_.value
			else
				i1.pos_.value = i2.value
			end if
			set i2.pos_.value = tmp
		else
			tmp = i1.pos_.value
			if isObject(i2.pos_.value) then
				set i1.pos_.value = i2.pos_.value
			else
				i1.pos_.value = i2.pos_.value
			end if
			i2.pos_.value = tmp
		end if
	end function

	'
	' Stack operations
	'

	' Push a new item onto the end of the list
	public sub push(value)
		dim n : set n = makeNode_(value, null, null)
		set n.prev_ = tail_.prev_
		set n.next_ = tail_
		set n.prev_.next_ = n
		set tail_.prev_ = n
	end sub

	' Pop an item off the end of the list, and return it
	public function pop
		mne_assert not head_ is tail_, "Pop called on empty list"

		if isObject(tail_.prev_.value) then
			set pop = tail_.prev_.value
		else	
			pop = tail_.prev_.value
		end if

		if count = 1 then
			set head_ = tail	
		else ' count > 1
			set tail_.prev_.prev_.next_ = tail_
			set tail_.prev_ = tail_.prev_.prev_
		end if
	end function

	' Push a new item onto the front of the list
	public sub pushFront(value)
		dim n : set n = makeNode_(value, head_, head_.next_)
		set head_.next_.prev_ = n
		set head_.next_ = n
	end sub

	' Pop an item off the front of the list, and return it
	public function popFront
		if count = 0 then
			popFront = null
		else
			if isObject(head_.next_.value) then
				set popFront = head_.next_.value
			else
				popFront = head_.next_.value
			end if

			set head_ = head_.next_
			set head_.next_.prev_ = head_
		end if
	end function

	' Return the first element in the list
	public function front
		if (count > 0) then
			if isObject(head_.next_.value) then
				set front = head_.next_.value
			else
				front = head_.next_.value
			end if
		else
			front = null
		end if
	end function

	' Return the last element in the list
	public function back
		if (count > 0) then
			if isObject(tail_.prev_.value) then
				set back = tail_.prev_.value
			else
				back = tail_.prev_.value
			end if
		else
			back = null
		end if
	end function
	
	'
	' Iteration and searching functions
	'
	
	' Find the given value, returning an iterator to it's position
	public function find(value)
		dim i : set i = begin
		set find = i
		while i() <> value
			if not i.moveNext then
				exit function
			end if
		wend
	end function

	' Find the given backwards, searching from the end of the list
	' return a reverse iterator to it's position
	public function rfind(value)
		dim i : set i = rbegin
		set rfind = i
		while i() <> value
			if not i.moveNext then
				exit function
			end if
		wend
	end function

	' Return a forward-iterator starting at the beginning of the list
	public function begin
		set begin = new mne_ListIterator
		set begin.pos_ = head_.next_
		set begin.end_ = tail_
	end function

	' Return the stop value for forward iterators
	public function finish
		set finish = new mne_ListIterator
		set finish.pos_ = tail_
		set finish.end_ = tail_
	end function

	' Return a reverse-iterator starting at the end of the list
	public function rbegin
		set rbegin = new mne_ListIterator
		rbegin.reverse_ = true
		set rbegin.pos_ = tail_.prev_
		set rbegin.end_ = head_
	end function

	' Return the stop value for reverse iterators
	public function rfinish
		set rfinish = new mne_ListIterator
		rfinish.reverse_ = true
		set rfinish.pos_ = head_
		set rfinish.end_ = head_
	end function

	'
	' Private Functions
	'

	' Make an interator from the given index
	private function makeItr_(index)
		if isObject(index) then
			' Assume it's an iterator
			set makeItr_ = index
		else
			mne_Assert index < count and index >= 0, "Index is out of bounds"
			' it's a number
			set makeItr_ = begin
			dim j : for j = 1 to index
				makeItr_.moveNext	
			next ' j 
		end if
	end function

	private function makeNode_(value, prev_, next_)
		set makeNode_ = new mne_ListNode
		if isObject(value) then
			set makeNode_.value = value
		else
			makeNode_.value = value
		end if

		if not isNull(next_) then set makeNode_.next_ = next_
		if not isNull(prev_) then set makeNode_.prev_ = prev_
	end function

	private head_
	private tail_
end class

%>
