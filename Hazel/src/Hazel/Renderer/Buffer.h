#pragma once

namespace Hazel
{
	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat2, Mat3, Mat4,
		Bool
	};

	static uint32_t GetSize(ShaderDataType type) {
		switch (type)
		{
			case ShaderDataType::Float: return 4;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 3;
			case ShaderDataType::Float4: return 4 * 4;
			case ShaderDataType::Int: return 4;
			case ShaderDataType::Int2: return 4 * 2;
			case ShaderDataType::Int3: return 4 * 3;
			case ShaderDataType::Int4: return 4 * 4;
			case ShaderDataType::Mat2: return 4 * 2 * 2;
			case ShaderDataType::Mat3: return 4 * 3 * 3;
			case ShaderDataType::Mat4: return 4 * 4 * 4;
			case ShaderDataType::Bool: return 1;
		}
		HZ_CORE_ASSERT(false, "unknown ShaderDataType");
		return 0;
	}
	static uint32_t GetComponentCount(ShaderDataType type)
	{
		switch (type) 
		{
			case ShaderDataType::Float: 
			case ShaderDataType::Int: return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Int2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Int3: return 3;
			case ShaderDataType::Float4: return 4 * 4;
			case ShaderDataType::Int4: return 4 * 4;
			case ShaderDataType::Mat2: return 2 * 2;
			case ShaderDataType::Mat3: return 3 * 3;
			case ShaderDataType::Mat4: return 4 * 4;
			case ShaderDataType::Bool: return 1;
		}
		HZ_CORE_ASSERT(false, "unknown ShaderDataType");
		return 0;
	}

	struct BufferAttribute
	{
		ShaderDataType type;
		std::string name;
		uint32_t size;
		size_t offset;
		bool normalized;

		BufferAttribute(ShaderDataType type, const std::string& name, bool normalized = false)
			: type(type), name(name), size(GetSize(type)), normalized(normalized) {}
	};

	class BufferLayout 
	{
	public:
		BufferLayout(const std::initializer_list<BufferAttribute>& attributes);
		
		const std::vector<BufferAttribute>& GetAttributes() const { return attributes; }
		std::vector<BufferAttribute>::iterator begin() { return attributes.begin(); }
		std::vector<BufferAttribute>::iterator end() { return attributes.end(); }
		uint32_t GetStride() const { return stride; }
	private:
		std::vector<BufferAttribute> attributes;
		uint32_t stride;
	};

	///////Vertex Buffer//////////////////////////////////////
	class VertexBuffer 
	{
	public:
		BufferLayout layout = {};
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const std::span<const float>& vertices) = 0;

		static VertexBuffer* Create(const std::span<const float>& vertices, BufferLayout layout);
	};

	///////Index Buffer//////////////////////////////////////
	class IndexBuffer 
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		uint32_t GetCount() const { return count; }
		virtual void SetData(const std::span<const uint32_t>& indices) = 0;

		static IndexBuffer* Create(const std::span<const uint32_t>& indices);
	protected:
		uint32_t count;
	};
}