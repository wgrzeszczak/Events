#pragma once
#include <algorithm>
#include <vector>
#include <functional>
#include <map>

namespace Events {
	typedef unsigned int EventToken;

	template<typename... TArgs>
	class Event {
	public:
		Event() {
			nextToken = 0;
		}
		Event(const Event& event) = delete;
		Event(Event&& event) noexcept = delete;
		Event& operator=(const Event& event) = delete;
		Event& operator=(Event&& event) noexcept = delete;
		~Event() = default;

		EventToken bind(std::function<void(const TArgs&&...)> callback) {
			EventToken token = nextToken++;
			callbacks[token] = callback;
			return token;
		}

		void unbind(EventToken token) {
			if(callbacks.find(token) == callbacks.end()) {
				return;
			}
			callbacks.erase(token);

			std::vector<EventToken> tokens;
			std::transform(callbacks.begin(), callbacks.end(), std::back_inserter(tokens),
				[](const std::map<EventToken, std::function<void(const TArgs&&...)>>::value_type& callback) {
					return callback.first;
				}
			);

			if(tokens.size()) {
				EventToken maxToken = *std::max_element(tokens.begin(), tokens.end());
				nextToken = ++maxToken;
			}
		}

		EventToken operator+=(std::function<void(const TArgs&&...)> callback) {
			return bind(callback);
		}

		void operator-=(EventToken token) {
			unbind(token);
		}

		void fire(const TArgs&... args) {
			for(auto& callback: callbacks) {
				callback.second(std::forward<const TArgs&&...>(args...));
			}
		}

	private:
		EventToken nextToken;
		std::map<EventToken, std::function<void(const TArgs&&...)>> callbacks;
	};
}