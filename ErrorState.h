#ifndef GMS_ErrorState_H
#define GMS_ErrorState_H
namespace GMS {

	class ErrorState {

		char* errorMessage;

	public:

		explicit ErrorState(const char* erM = nullptr);
		ErrorState(const ErrorState& em) = delete;
		ErrorState& operator=(const ErrorState& em) = delete;
		virtual ~ErrorState();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
	};
	std::ostream& operator<<(std::ostream& cout, const ErrorState& erSt);
}
#endif // !GMS_ErrorState_H