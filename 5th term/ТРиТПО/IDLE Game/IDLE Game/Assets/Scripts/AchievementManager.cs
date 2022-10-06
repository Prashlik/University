using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using BreakInfinity;
using static BreakInfinity.BigDouble;

public class AchievementManager : MonoBehaviour
{
    public IDLEGame game;
    private static string[] AchievementStrings => new string[] { "Current $", "Total $" };
    private BigDouble[] AchievementsNumbers => new BigDouble[] { game.data.count, game.data.totalcount };

    public GameObject achievementScreen;
    public List<Achievement> achievementList = new List<Achievement>();

    public void StartAchiev()
    {
        foreach (var x in achievementScreen.GetComponentsInChildren<Achievement>())
            achievementList.Add(x);
    }

    public void RunAchievements()
    {
        var data = game.data;
        UpdateAchievement(AchievementStrings[0], AchievementsNumbers[0], ref data.AchLv1, ref achievementList[0].fill,
            ref achievementList[0].title, ref achievementList[0].progress);
        UpdateAchievement(AchievementStrings[1], AchievementsNumbers[1], ref data.AchLv2, ref achievementList[1].fill,
            ref achievementList[1].title, ref achievementList[1].progress);
    }

    private void UpdateAchievement(string name, BigDouble number, ref float level, ref Image fill, ref Text title, ref Text progress)
    {
        var cap = BigDouble.Pow(10, level);

        if (game.AchievementsGroup.gameObject.activeSelf)
        {
            title.text = $"{name}\n ({level})";
            progress.text = $"{Methods.NotationMethod(number, "F2")} / {Methods.NotationMethod(cap, "F2")}";

            Methods.BigDoubleFill(number, cap, fill);
        }
        if (number < cap) return;
        BigDouble levels = 0;
        if (number / cap >= 1)
            levels = Floor(Log10(number / cap)) + 1;
        level += (float)levels;
    }
}
