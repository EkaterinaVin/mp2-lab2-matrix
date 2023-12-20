#include "tmatrix.h" 

#include <gtest.h> 

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	int* mas = new int[3] { 1, 1, 1};
	TDynamicVector<int> a(mas, 3), b(a);
	EXPECT_EQ(a, b);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)//не точно 
{
	int* mas = new int[3] { 1, 1, 1 };
	TDynamicVector<int> a(mas, 3), b(a);
	EXPECT_NE(&a, &b);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element) 
{ 
  TDynamicVector<int> v(4); 
  v[0] = 4; 
 
  EXPECT_EQ(4, v[0]); 
} 

TEST(TDynamicVector, throws_when_set_element_with_negative_index)//чек-чек 
{
	TDynamicVector<int> v(3);
	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)//чек-чек 
{
	TDynamicVector<int> v(3);
	ASSERT_ANY_THROW(v.at(4));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(3);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> a(3), b(3);
	ASSERT_NO_THROW(a = b);
	EXPECT_EQ(a, b);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> a(3), b(4);
	ASSERT_NO_THROW(a = b);
	EXPECT_EQ(a.size(), b.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> a(3), b(4);
	ASSERT_NO_THROW(a = b);
	EXPECT_EQ(a, b);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int* mas1 = new int[3] { 1, 1, 1 };
	int* mas2 = new int[3] { 1, 1, 1 };
	TDynamicVector<int> a(mas1, 3), b(mas2, 3);
	EXPECT_EQ(a, b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	int* mas1 = new int[3] { 1, 1, 1 };
	TDynamicVector<int> a(mas1, 3);
	EXPECT_EQ(a, a);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	int* mas1 = new int[3] { 1, 1, 1 };
	int* mas2 = new int[4] { 1, 1, 1, 1 };
	TDynamicVector<int> a(mas1, 3), b(mas2, 4);
	EXPECT_NE(a, b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int* mas1 = new int[3] { 1, 1, 1 };
	int* mas2 = new int[3] { 2, 2, 2 };
	TDynamicVector<int> a(mas1, 3), b(mas2, 3);
	a = a + 1;
	EXPECT_EQ(a, b);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int* mas1 = new int[3] { 1, 1, 1 };
	int* mas2 = new int[3] { 2, 2, 2 };
	TDynamicVector<int> a(mas1, 3), b(mas2, 3);
	b = b - 1;
	EXPECT_EQ(a, b);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int* mas1 = new int[3] { 1, 1, 1 };
	int* mas2 = new int[3] { 2, 2, 2 };
	TDynamicVector<int> a(mas1, 3), b(mas2, 3);
	a = a * 2;
	EXPECT_EQ(a, b);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int* mas1 = new int[3] { 1, 1, 1 };
	int* mas2 = new int[3] { 1, 1, 1 };
	int* mas3 = new int[3] { 2, 2, 2 };
	TDynamicVector<int> a(mas1, 3), b(mas3, 3), c(mas2, 3);
	EXPECT_EQ(a + c, b);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	int* mas1 = new int[3] { 1, 1, 1 };
	int* mas2 = new int[4] { 2, 2, 2, 2};
	TDynamicVector<int> a(mas1, 3), b(mas2, 4);
	ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int* mas1 = new int[3] { 4, 4, 4 };
	int* mas2 = new int[3] { 2, 2, 2 };
	int* mas3 = new int[3] { 2, 2, 2 };
	TDynamicVector<int> a(mas1, 3), b(mas3, 3), c(mas2, 3);
	EXPECT_EQ(a - b, c);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	int* mas1 = new int[3] { 1, 1, 1 };
	int* mas2 = new int[4] { 2, 2, 2, 2};
	TDynamicVector<int> a(mas1, 3),b(mas2, 4);
	ASSERT_ANY_THROW(a - b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	/*int* mas1 = new int[3] { 4, 4, 4 };*/
	int* mas2 = new int[3] { 2, 2, 2 };
	int* mas3 = new int[3] { 2, 2, 2 };
	TDynamicVector<int>  b(mas3, 3), c(mas2, 3);
	EXPECT_EQ(b * c, 12);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	int* mas1 = new int[3] { 1, 1, 1 };
	int* mas2 = new int[4] { 2, 2, 2, 2};
	TDynamicVector<int> a(mas1, 3), b(mas2, 4);
	ASSERT_ANY_THROW(a * b);
}
