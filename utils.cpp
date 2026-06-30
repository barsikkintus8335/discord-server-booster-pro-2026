using System;

namespace SpotifyAdRemover
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("=== Spotify AdRemover Pro 2026 ===");
            Console.WriteLine("[Info] Starting Spotify window monitor...");

            SpotifyMonitor monitor = new SpotifyMonitor(500);
            
            monitor.OnAdStateChanged += (isAd) =>
            {
                if (isAd)
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine($"[{DateTime.Now.ToLongTimeString()}] [AD DETECTED] Muting audio session...");
                }
                else
                {
                    Console.ForegroundColor = ConsoleColor.Green;
                    Console.WriteLine($"[{DateTime.Now.ToLongTimeString()}] [TRACK PLAYING] Unmuting audio session.");
                }
                Console.ResetColor();
            };

            monitor.Start();

            Console.WriteLine("[Info] Monitor active. Press ESC to exit.");
            while (Console.ReadKey(true).Key != ConsoleKey.Escape) {}

            monitor.Stop();
            Console.WriteLine("[Info] Application closed.");
        }
    }
}