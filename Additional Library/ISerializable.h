#pragma once

//Created by: Krzysztof Mochocki

#include <stdexcept>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <array>

class ISerializable abstract
{
public:

	virtual void Serialize(std::ofstream*, ...) = 0;

	virtual void Deserialize(std::ifstream*, ...) = 0;
		
	static struct Static
	{
		static struct Single
		{
			template<typename T>
			static void save(std::ofstream* output, const T obj)
			{
				if (output == nullptr) try { throw  std::invalid_argument("cannot be nullptr"); } catch (...) { throw; }

				output->write((char*)&obj, sizeof(T));
			}

			template<typename T>
			static void load(std::ifstream* input, T* dst)
			{
				if (dst == nullptr || input == nullptr) try { throw  std::invalid_argument("cannot be nullptr"); } catch (...) { throw; }

				input->read((char*)dst, sizeof(T));
			}
		};

		static struct Array
		{
			template<typename T>
			static void save(std::ofstream* output, const T* Array, const size_t ArraySize)
			{
				if (Array == nullptr || output == nullptr) try { throw  std::invalid_argument("cannot be nullptr"); } catch (...) { throw; }

				ISerializable::Static::Single::save(output, ArraySize);
				for (int i = 0; i < ArraySize; i++)
					ISerializable::Static::Single::save(output, Array[i]);
				
				
			}

			template<typename T>
			static void load(std::ifstream* input, T* Array, size_t* ArraySize)
			{
				if (Array == nullptr || input == nullptr || ArraySize == nullptr) try { throw  std::invalid_argument("cannot be nullptr"); } catch (...) { throw; }

				ISerializable::Static::Single::load(input, ArraySize);
				for (int i = 0; i < *ArraySize; i++)
					ISerializable::Static::Single::load(input, &(Array[i]));
			}
		};
	};

	static struct Dynamic
	{
		static struct Single
		{

			template<typename T>
			static void save(std::ofstream* output, T** obj)
			{
				if (output == nullptr) try { throw  std::invalid_argument("obj cannot be nullptr"); }catch (...) { throw; }
				if (is_pointer<T>::value || is_reference<T>::value) try { throw  std::invalid_argument("Type cannot be a pointer, must be an object."); }catch (...) { throw; }

				output->write((char*)*obj, sizeof(T));
			}
			
			template<typename T>
			static void load(std::ifstream* input, T** dst)
			{
				if (input == nullptr) try { throw  std::invalid_argument("cannot be nullptr"); } catch (...) { throw; }
				if (is_pointer<T>::value || is_reference<T>::value) try { throw  std::invalid_argument("Type cannot be a pointer, must be an object."); }catch (...) { throw; }

				free(*dst);
				(*dst) = nullptr;
				(*dst) = (T*)(malloc(sizeof(T)));

				input->read((char*)(*dst), sizeof(T));
			}
		};

		static struct Array
		{
			template<typename T>
			static void save(std::ofstream* output, T** Array, const size_t ArraySize)
			{
				if (output == nullptr) try { throw  std::invalid_argument("cannot be nullptr."); } catch (...) { throw; }
				if (is_pointer<T>::value || is_reference<T>::value) try { throw  std::invalid_argument("Type cannot be a pointer, must be an object."); }catch (...) { throw; }

				ISerializable::Static::Single::save(output, ArraySize);
				for (int i = 0; i < ArraySize; i++)
				{
					ISerializable::Static::Single::save(output, (*Array)[i]);
				}
			}

			template<typename T>
			static void load(std::ifstream* input, T** Array, size_t* ArraySize)
			{
				if (input == nullptr || ArraySize == nullptr) try { throw  std::invalid_argument("cannot be nullptr"); } catch (...) { throw; }
				if (is_pointer<T>::value || is_reference<T>::value) try { throw  std::invalid_argument("Type cannot be a pointer, must be an object."); } catch (...) { throw; }

				ISerializable::Static::Single::load(input, ArraySize);

				free(*Array);
				(*Array) = nullptr;
				(*Array) = (T*)(malloc((*ArraySize) * sizeof(T)));

				for (int i = 0; i < *ArraySize; i++)
				{
					ISerializable::Static::Single::load(input, &((*Array)[i]));
				}
			}
		};
	};

	static struct StandardLibrary
	{
		static struct Vector
		{
			template<typename T>
			static void save(std::ofstream *const output, const std::vector<T> *const src)
			{
				if (output == nullptr || src == nullptr) try { throw  std::invalid_argument("Cannot be nullptr"); }catch (...) { throw; }
				if (is_pointer<T>::value || is_reference<T>::value) try { throw std::invalid_argument("Type cannot be a pointer, must be an object."); }catch (...) { throw; }

				auto itBegin = src->begin();
				const auto itEnd = src->end();

				ISerializable::Static::Single::save(output, src->size());
				
				T temp;

				for (itBegin; itBegin != itEnd; itBegin++)
				{
					temp = *itBegin;
					ISerializable::Static::Single::save(output, temp);
				}
			}

			template<typename T>
			static void load(std::ifstream *const input, std::vector<T> *const src)
			{
				if (input == nullptr || src == nullptr) try { throw  std::invalid_argument("Cannot be nullptr"); } catch (...) { throw; }
				if (is_pointer<T>::value || is_reference<T>::value) try { throw  std::invalid_argument("Type cannot be a pointer, must be an object."); } catch (...) { throw; }

				size_t SizeOfVector;
				ISerializable::Static::Single::load(input, &SizeOfVector);

				T temp;

				for (int i = 0; i < SizeOfVector; i++)
				{
					ISerializable::Static::Single::load(input, &temp);
					src->push_back(temp);
				}
			}
		};

		static struct List
		{
			template<typename T>
			static void save(std::ofstream * const output, const std::list<T> * const src)
			{
				if (output == nullptr || src == nullptr) try { throw  std::invalid_argument("Cannot be nullptr"); }catch (...) { throw; }
				if (is_pointer<T>::value || is_reference<T>::value) try { throw std::invalid_argument("Type cannot be a pointer, must be an object."); }catch (...) { throw; }

				auto itBegin = src->begin();
				const auto itEnd = src->end();
				size_t size = src->size();

				ISerializable::Static::Single::save(output, (size));

				T temp;

				for (itBegin; itBegin != itEnd; itBegin++)
				{
					temp = *itBegin;
					ISerializable::Static::Single::save(output, temp);
				}
					
			}

			template<typename T>
			static void load(std::ifstream * const input, std::list<T> * const dst)
			{
				if (input == nullptr || dst == nullptr) try { throw  std::invalid_argument("Cannot be nullptr"); }catch (...) { throw; }
				if (is_pointer<T>::value || is_reference<T>::value) try { throw std::invalid_argument("Type cannot be a pointer, must be an object."); }catch (...) { throw; }
			
				size_t dstSize = 0;
				ISerializable::Static::Single::load(input, &dstSize);

				T temp;

				for (int i = 0; i < dstSize; i++)
				{
					ISerializable::Static::Single::load(input, &temp);
					dst->push_back(temp);
				}
			}

		};

		static struct Queue
		{

			template<typename T>
			static void save(std::ofstream * const output, std::queue<T> * src)
			{
				if (output == nullptr || src == nullptr) try { throw  std::invalid_argument("Cannot be nullptr"); }catch (...) { throw; }
				if (is_pointer<T>::value || is_reference<T>::value) try { throw std::invalid_argument("Type cannot be a pointer, must be an object."); }catch (...) { throw; }
												
				const size_t qSize = src->size();
				ISerializable::Static::Single::save(output, qSize);

				std::queue<T> * temp = new std::queue<T>;
				(*temp) = *src;

				for (int i = 0; i < qSize; i++)
				{
					ISerializable::Static::Single::save(output, src->front());
					src->pop();
				}

				//free(src);
				*src = *temp;
				temp = nullptr;
			}

			template<typename T>
			static void load(std::ifstream * const input, std::queue<T> * const dst)
			{
				if (input == nullptr || dst == nullptr) try { throw  std::invalid_argument("Cannot be nullptr"); }catch (...) { throw; }
				if (is_pointer<T>::value || is_reference<T>::value) try { throw std::invalid_argument("Type cannot be a pointer, must be an object."); }catch (...) { throw; }

				size_t qSize;
				ISerializable::Static::Single::load(input, &qSize);

				T temp;

				for (int i = 0; i < qSize; i++)
				{
					ISerializable::Static::Single::load(input, &temp);
					dst->push(temp);
				}
			}

		};

		static struct Stack
		{
			template<typename T>
			static void save(std::ofstream * const output, std::stack<T> * src)
			{
				if (output == nullptr || src == nullptr) try { throw  std::invalid_argument("Cannot be nullptr"); }catch (...) { throw; }
				if (is_pointer<T>::value || is_reference<T>::value) try { throw std::invalid_argument("Type cannot be a pointer, must be an object."); }catch (...) { throw; }

				const size_t Ssize = src->size();
				ISerializable::Static::Single::save(output, Ssize);

				std::stack<T> * Backup = new std::stack<T>;
				*Backup = *src;

				for (int i = 0; i < Ssize; i++)
				{
					//In loading SWAP!!!
					ISerializable::Static::Single::save(output, src->top());
					src->pop();
				}

				*src = *Backup;
			}

			template<typename T>
			static void load(std::ifstream * const input, std::stack<T> * dst)
			{
				if (input == nullptr || dst == nullptr) try { throw  std::invalid_argument("Cannot be nullptr"); }catch (...) { throw; }
				if (is_pointer<T>::value || is_reference<T>::value) try { throw std::invalid_argument("Type cannot be a pointer, must be an object."); }catch (...) { throw; }

				size_t Ssize;
				ISerializable::Static::Single::load(input, &Ssize);

				T temp;

				for (int i = 0; i < Ssize; i++)
				{
					ISerializable::Static::Single::load(input, &temp);
					dst->push(temp);
				}

				stack_swap(dst);
			}

		private:

			template<typename T>
			static void stack_swap(std::stack<T> * src)
			{
				std::stack<T>* temp = new std::stack<T>;
				const size_t size = src->size();

				for (int i = 0; i < size; i++)
				{
					temp->push(src->top());
					src->pop();
				}

				src->swap(*temp);
				delete temp;
				temp = nullptr;
			}

		};

		static struct Array
		{
			template<typename T, const size_t ArraySize>
			static void save(std::ofstream * const output, const std::array<T, ArraySize> * const src)
			{
				if (output == nullptr || src == nullptr) try { throw  std::invalid_argument("Cannot be nullptr"); }catch (...) { throw; }
				if (is_pointer<T>::value || is_reference<T>::value) try { throw std::invalid_argument("Type cannot be a pointer, must be an object."); }catch (...) { throw; }
				
				for (int i = 0; i < ArraySize; i++)
					ISerializable::Static::Single::save(output, (*src)[i]);
			}
			
			template<typename T, const size_t ArraySize>
			static void load(std::ofstream * const input, std::array<T, ArraySize> * const dst)
			{
				if (input == nullptr || dst == nullptr) try { throw  std::invalid_argument("Cannot be nullptr"); }catch (...) { throw; }
				if (is_pointer<T>::value || is_reference<T>::value) try { throw std::invalid_argument("Type cannot be a pointer, must be an object."); }catch (...) { throw; }

				for (int i = 0; i < ArraySize; i++)
					ISerializable::Static::Single::load(input, (*dst)[i]); 
			}
		};
	};

};