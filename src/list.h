#ifndef LIST_H_
#define LIST_H_

#include <iostream>

namespace cds
{
	template<typename T>
	class List
	{
	private:
		struct Node
		{
			Node() : m_next(NULL) {}
			Node(const T& data) : m_data(data), m_next(NULL) {}

			T m_data;
			Node* m_next;
		};

		Node* m_head;
	public:
		class Iterator
		{
		private:
			Node* m_node;
		public:
			Iterator(Node* node) : m_node(node) {}
			
			bool operator==(const Iterator& other) const
			{
				if (this == &other)
				{
					return true;
				}

				return m_node == other.m_node;
			}

			bool operator!=(const Iterator& other) const
			{
				return !operator==(other);
			}

			T operator*() const
			{
				if (m_node)
				{
					return m_node->m_data;
				}
				return T();
			}

			void operator++()
			{
				if(m_node)
				{
					m_node = m_node->m_next;
				}
			}
		};
	public:
		List();
		~List();

		void append(const T& data);
		void remove();

		T head() const;
		Iterator begin() const;
		Iterator end() const;
		
		std::size_t size() const;
	};


	//      definition

	template<typename T>
	List<T>::List() 
		: 
		m_head(NULL)
	{
		//
	}

	template<typename T>
	void List<T>::append(const T& data)
	{
		Node* node = new Node(data);
		node->m_next = m_head;
		m_head = node;
	}

	template<typename T>
	void List<T>::remove()
	{
		if (m_head)
		{
			Node* new_head = m_head->m_next;
			delete m_head;

			m_head = new_head;
		}
	}

	template<typename T>
	List<T>::~List()
	{
		while (m_head)
			remove();
	}

	template<typename T>
	T List<T>::head() const
	{
		return m_head->m_data;
	}

	template<typename T>
	typename List<T>::Iterator List<T>::begin() const
	{
		return Iterator(m_head);
	}

	template<typename T>
	typename List<T>::Iterator List<T>::end() const
	{
		return Iterator(NULL);
	}

	template<typename T>
	std::size_t List<T>::size() const
	{
		std::size_t s = 0;
		for(Iterator it = begin(); it != end(); ++it)
		{
			++s;
		}

		return s;
	}

}	// cds

#endif	// LIST_H_