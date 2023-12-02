#pragma once

#include "token_swapping/instance.hpp"

#include <array>
#include <memory>

namespace TokenSwapping
{
	template <int n>
	class DatabaseTreeNode;

	template <int n>
	class DatabaseTreeNode
	{
	public:
		DatabaseTreeNode(int depth);
		int read(const Instance& instance) const;
		void write(const Instance& instance, int value);

	private:
		std::array<std::unique_ptr<DatabaseTreeNode>, n> m_children;
		int m_depth;
		int m_value;
	};

	template <int n>
	class DatabaseTree
	{
	public:
		int read(const Instance& instance) const;
		void write(const Instance& instance, int value);

	private:
		std::unique_ptr<DatabaseTreeNode<n>> m_root;
	};

	template <int n>
	DatabaseTreeNode<n>::DatabaseTreeNode(int depth) :
		m_depth{depth},
		m_value{-1}
	{ }

	template <int n>
	int DatabaseTreeNode<n>::read(const Instance& instance) const
	{
		if (instance.size() == m_depth)
		{
			return m_value;
		}
		else if (m_children[instance[m_depth]])
		{
			return m_children[instance[m_depth]]->read(instance);
		}
		else
		{
			return -1;
		}
	}

	template <int n>
	void DatabaseTreeNode<n>::write(const Instance& instance, int value)
	{
		if (instance.size() == m_depth)
		{
			m_value = value;
		}
		else
		{
			if(!m_children[instance[m_depth]])
			{
				m_children[instance[m_depth]] = std::make_unique<DatabaseTreeNode<n>>(m_depth + 1);
			}
			m_children[instance[m_depth]]->write(instance, value);
		}
	}

	template <int n>
	int DatabaseTree<n>::read(const Instance& instance) const
	{
		if (m_root)
		{
			return m_root->read(instance);
		}
		else
		{
			return -1;
		}
	}

	template <int n>
	void DatabaseTree<n>::write(const Instance& instance, int value)
	{
		if (!m_root)
		{
			m_root = std::make_unique<DatabaseTreeNode<n>>(0);
		}
		m_root->write(instance, value);
	}
};
