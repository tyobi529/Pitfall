# pragma once
# include <Siv3D.hpp>

namespace Tween
{
    struct trans_t
    {
        double to;
        Duration begin, end;
        std::function<double(double)> easingFunction = EaseInLinear;
    };

    // template <typename T>
    class Timeline
    {
    public:

        explicit Timeline(const double initialValue = 0.0, bool startImmediately = false)
            :m_initialValue(initialValue), m_value(initialValue), m_isRunning(false)
        {
            if (startImmediately)
            {
                m_isRunning = true;
                m_stopwatch.start();
            }
        }

		void Init(const double initialValue = 0.0, bool startImmediately = false)
		{
			clear();
			m_initialValue = initialValue;
			m_value = initialValue;
			m_isRunning = false;

			if (startImmediately)
			{
				m_isRunning = true;
				m_stopwatch.start();
			}
		}

        ~Timeline()
        {
        }

        Timeline& then(const double to, const Duration dur = 0.0s, double easingFunction(double) = EaseInLinear)
        {
            addTransition(to, dur, easingFunction);
            return *this;
        }

        Timeline& wait(const Duration dur)
        {
            const double prevTarget = (m_transitions.isEmpty() ? 0 : m_transitions.back().to);
            addTransition(prevTarget, dur, EaseInLinear);
            return *this;
        }

        bool update()
        {
            if (m_transitions.isEmpty()) return false;

            if (m_transitions.size() <= m_currentIndex)
            {
                m_value = m_transitions.back().to;
                m_isRunning = false;
                return false;
            }

            if (m_transitions[m_currentIndex].end < m_stopwatch.elapsed()) {
                m_currentIndex++;
                if (m_transitions.size() <= m_currentIndex)
                {
                    m_value = m_transitions.back().to;
                    m_isRunning = false;
                    return false;
                }
            }

            const double t = (m_transitions[m_currentIndex].end - m_transitions[m_currentIndex].begin).count();
            const double c = m_transitions[m_currentIndex].to - (m_currentIndex > 0 ? m_transitions[m_currentIndex - 1].to : m_initialValue);
            double e = 1;
            if (t > 0) e = m_transitions[m_currentIndex].easingFunction(Min((m_stopwatch.sF() - m_transitions[m_currentIndex].begin.count()), t) / t);

            m_value = c*e + (m_currentIndex > 0 ? m_transitions[m_currentIndex - 1].to : m_initialValue);

            return true;
        }

        void start() { m_isRunning = true; m_stopwatch.start(); }
        void clear()
        {
            m_currentIndex = 0;
            m_initialValue = 0.0;
            m_transitions.clear();
            m_isRunning = false;
            m_value = 0.0;
            m_stopwatch.reset();
        }
        void restart()
        {
            m_currentIndex = 0;
            m_value = m_initialValue;
            m_stopwatch.restart();
        }
        bool isEmpty() { return m_transitions.isEmpty(); }
        bool isRunning() { return m_isRunning; }
        size_t size() { return m_transitions.size(); }
        double getValue() { return m_value; }
        double operator()() { return getValue(); }
        Duration elapsed() { return m_stopwatch.elapsed(); }

    private:
        void addTransition(const double to, const Duration dur, double easingFunction(double))
        {
            const Duration prevDur = (m_transitions.isEmpty() ? 0.0s : m_transitions.back().end);
            m_transitions.emplace_back(trans_t{ to, prevDur, prevDur + dur, easingFunction });
        }

        Stopwatch m_stopwatch;
        Array<trans_t> m_transitions;
        int32 m_currentIndex = 0;
        double m_initialValue = 0.0;
        double m_value = 0.0;
        bool m_isRunning;
    };
}
