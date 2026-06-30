using System;
using System.Diagnostics;
using System.Text;
using System.Timers;

namespace SpotifyAdRemover
{
    public class SpotifyMonitor
    {
        private Timer _timer;
        private string _lastTitle = string.Empty;
        
        public event Action<bool> OnAdStateChanged;

        public SpotifyMonitor(double intervalMs = 1000)
        {
            _timer = new Timer(intervalMs);
            _timer.Elapsed += Timer_Elapsed;
        }

        public void Start() => _timer.Start();
        public void Stop() => _timer.Stop();

        private void Timer_Elapsed(object sender, ElapsedEventArgs e)
        {
            Process[] processes = Process.GetProcessesByName("Spotify");
            if (processes.Length == 0) return;

            foreach (var process in processes)
            {
                if (!string.IsNullOrEmpty(process.MainWindowTitle))
                {
                    string currentTitle = process.MainWindowTitle;

                    if (currentTitle != _lastTitle)
                    {
                        _lastTitle = currentTitle;
                        CheckTitle(currentTitle);
                    }
                    break;
                }
            }
        }

        private void CheckTitle(string title)
        {
            bool isAd = title.Equals("Advertisement", StringComparison.OrdinalIgnoreCase) || 
                        title.Equals("Реклама", StringComparison.OrdinalIgnoreCase) ||
                        title.Equals("Spotify", StringComparison.OrdinalIgnoreCase);

            OnAdStateChanged?.Invoke(isAd);
        }
    }
}