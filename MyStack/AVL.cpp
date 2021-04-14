#include "AVL.h"

template<class T>
bool AVL<T>::insert(const T& ele) {
	Node<T>* tmp = insert(root, ele);
	if (tmp) {
		root = tmp;
		return true;
	}
	return false;
}

template<class T>
bool AVL<T>::remove(const T& ele) {
	Node<T>* tmp = remove(root, ele);
	if (tmp) {
		_size--;
		root = tmp;
		return true;
	}
	return false;
}

template<class T>
AVL<T>::Node<T>* AVL<T>::insert(TreeNode<T>* node, const T& ele) {
	if (!node)
		return new Node<T>(ele);
	if (ele < node->ele)
		node->left = insert(node->left, ele);
	else if (ele > node->ele)
		node->right = insert(node->right, ele);
	else
		return NULL;
	return balance(node);
}

template<class T>
AVL<T>::Node<T>* AVL<T>::balance(TreeNode<T>* _node) {
	if (!_node)
		return nullptr;
	Node<T>* node = (Node<T>*)_node;
	// �����ߴ�������
	if(get_height(node->left) - get_height(node->right) > ALLOW_BALANCE)
		if (get_height(node->left->left) >= get_height(node->left->right))
			node = rotate_with_left_child(node); //��������ߣ�����ת
		else
			node = double_rotate_with_left_child(node); //�ڲ������ߣ�˫��ת
	//�Գ����
	else if (get_height(node->right) - get_height(node->left) > ALLOW_BALANCE)
		if (get_height(node->right->right) >= get_height(node->right->left))
			node = rotate_with_right_child(node); //��������ߣ�����ת
		else
			node = double_rotate_with_right_child(node); //�ڲ������ߣ�˫��ת
	node->height = max(get_height(node->left), get_height(node->right)) + 1;
	return node;
}

//�������ߵĵ���ת
template<class T>
AVL<T>::Node<T>* AVL<T>::rotate_with_left_child(TreeNode<T>* _k2) {
	Node<T>* k2 = (Node<T>*)_k2;
	Node<T>* k1 = (Node<T>*)k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(get_height(k2->left), get_height(k2->right)) + 1;
	k1->height = max(get_height(k1->left), get_height(k1->right)) + 1;
	return k1;
}

//�������ߵ�˫��ת
template<class T>
AVL<T>::Node<T>* AVL<T>::double_rotate_with_left_child(TreeNode<T>* k3) {
	k3->left = rotate_with_left_child(k3->left);
	return rotate_with_right_child(k3);
}

//�������ߵĵ���ת
template<class T>
AVL<T>::Node<T>* AVL<T>::rotate_with_right_child(TreeNode<T>* _k2) {
	Node<T>* k2 = (Node<T>*)_k2;
	Node<T>* k1 = (Node<T>*)k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max(get_height(k2->left), get_height(k2->right)) + 1;
	k1->height = max(get_height(k1->left), get_height(k1->right)) + 1;
	return k1;
}

//�������ߵ�˫��ת
template<class T>
AVL<T>::Node<T>* AVL<T>::double_rotate_with_right_child(TreeNode<T>* k3) {
	k3->right = rotate_with_left_child(k3->right);
	return rotate_with_right_child(k3);
}

template<class T>
AVL<T>::Node<T>* AVL<T>::remove(TreeNode<T>* node, const T& ele) {
	if (!node) {
		return NULL;
	} else if (node->ele > ele) {
		node->left = remove(node->left, ele);
	} else if(node->ele < ele){
		node->right = remove(node->right, ele);
	} else if (node->left && node->right) {
		// ��Ȳ�������������
		TreeNode<T>* tmp = node->right;
		while (tmp->left) tmp = tmp->left; // findMin
		node->ele = tmp->ele;
		node->right = remove(node->right, node->ele);
	} else {
		// ֻ��һ������
		TreeNode<T>* origin = node;
		node = (node->left ? node->left : node->right);
		delete origin;
	}
	return balance(node);
}

template<class T>
int AVL<T>::get_height(TreeNode<T>* node) {
	return node ? ((Node<T>*)node)->height : -1;
}
