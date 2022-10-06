using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using BreakInfinity;
using System;
using static BreakInfinity.BigDouble;

public class IDLEGame : MonoBehaviour
{
    public PlayData data;
    public DEManager events;
    public PrestigeManager prestige;
    public AchievementManager achievements;
    public OfflineManager offline;

    public Text CountText;      //счётчик очков
    public Text CountValueText; //+ кол-во очков при нажатии

    public Text CountSecText;   //счётчик прироста

    public Text ClickUpgr1Text;  //кнопка увелчения кол-ва нажатий ур.1

    public Text TimeUpgr1Text;   //кнопка пассивного дохода ур.1

    public Text ClickUpgr2Text;  //кнопка увелчения кол-ва нажатий ур.2

    public Text TimeUpgr2Text;   //кнопка пассивного дохода ур.2

    public Text MaxCU1Text;     //кнопки апгрейда на все деньги
    public Text MaxCU2Text;
    public Text MaxTU1Text;
    public Text MaxTU2Text;

    public Canvas GameMenuGroup;
    public Canvas UpgrMenuGroup;
    public Canvas AchievementsGroup;
    public Canvas EventGroup;

    public GameObject settings;

    private BigDouble CU1NowCost => 20 * Pow(1.2, data.CU1Level);
    private BigDouble TU1NowCost => 50 * Pow(1.2, data.TU1Level);
    private BigDouble CU2NowCost => 150 * Pow(1.5, data.CU2Level);
    private BigDouble TU2NowCost => 250 * Pow(1.5, data.TU2Level);

    public float saveTimer;

    public void Start()
    {
        Application.targetFrameRate = 60;   //фиксация частоты кадров = 60

        GameMenuGroup.gameObject.SetActive(true);
        UpgrMenuGroup.gameObject.SetActive(false);
        AchievementsGroup.gameObject.SetActive(false);
        EventGroup.gameObject.SetActive(false);
        prestige.prestige.gameObject.SetActive(false);

        SaveSystem.LoadPlayer(ref data);
        events.StartEvents();
        prestige.StartPrestige();
        achievements.StartAchiev();
        TotalCoinsPerSec();
        offline.LoadOfflineProduction();
    }

    public void UpdrMaxNumb()
    {
        data.CU1Max = Floor(Log(((data.count * (1.2 - 1)) / (20 * Pow(1.2, data.CU1Level))) + 1, 1.2));
        data.CU2Max = Floor(Log(((data.count * (1.5 - 1)) / (150 * Pow(1.5, data.CU2Level))) + 1, 1.5));
        data.TU1Max = Floor(Log(((data.count * (1.2 - 1)) / (50 * Pow(1.2, data.TU1Level))) + 1, 1.2));
        data.TU2Max = Floor(Log(((data.count * (1.5 - 1)) / (250 * Pow(1.5, data.TU2Level))) + 1, 1.5));
    }

    public void Update()
    {
        achievements.RunAchievements();
        prestige.Run();
        UpdrMaxNumb();

        CountText.text = "$" + Methods.NotationMethod(data.count, "F2");
        CountSecText.text = "$" + Methods.NotationMethod(TotalCoinsPerSec(), "F2") + " /sec";

        if (GameMenuGroup.gameObject.activeSelf)
            CountValueText.text = "+$" + Methods.NotationMethod(TotalClickValue(), "F2");

        if (UpgrMenuGroup.gameObject.activeSelf)
        {
            ClickUpgr1Text.text = "CLICK UPGRADE 1\n Cost: " + Methods.NotationMethod(CU1NowCost, "F2") + "\nPower: +$" 
                + Methods.NotationMethod(events.eventTokenBoost * Pow(1.5, prestige.levels[0]), "F2") + "\n Level: " + data.CU1Level.ToString("F0");
            MaxCU1Text.text = "BUY MAX CU1 ( " + data.CU1Max.ToString("F0") + " )";

            TimeUpgr1Text.text = "TIME UPGRADE 1\n Cost: " + Methods.NotationMethod(TU1NowCost, "F2") + "\nPower: +$" + TotalBoost().ToString("F2")
    + " /sec\n Level: " + data.TU1Level.ToString("F0");
            MaxTU1Text.text = "BUY MAX TU1 ( " + data.TU1Max.ToString("F0") + " )";

            ClickUpgr2Text.text = "CLICK UPGRADE 2\n Cost: " + Methods.NotationMethod(CU2NowCost, "F2") + "\nPower: +$" 
                + Methods.NotationMethod(data.CU2Power * events.eventTokenBoost * Pow(1.5, prestige.levels[0]), "F2") + "\n Level: " + data.CU2Level.ToString("F0");
            MaxCU2Text.text = "BUY MAX CU2 ( " + data.CU2Max.ToString("F0") + " )";

            TimeUpgr2Text.text = "TIME UPGRADE 2\n Cost: " + Methods.NotationMethod(TU2NowCost, "F2") + "\nPower: +$" + (TotalBoost() * data.TU2Power).ToString("F2")
    + " /sec\n Level: " + data.TU2Level.ToString("F0");
            MaxTU2Text.text = "BUY MAX TU2 ( " + data.TU2Max.ToString("F0") + " )";
        }

        data.count += TotalCoinsPerSec() * Time.deltaTime;
        data.totalcount += TotalCoinsPerSec() * Time.deltaTime;

        saveTimer += Time.deltaTime;

        if (saveTimer < 5) return;
        SaveSystem.SavePlayer(data);
        saveTimer = 0;
    }

    private BigDouble TotalClickValue()
    {
        var temp = data.ClickValue;
        temp *= events.eventTokenBoost;
        temp *= Pow(1.5, prestige.levels[0]);
        return temp;
    }

    public BigDouble TotalCoinsPerSec()
    {
        BigDouble temp = 0;
        temp += data.TU1Level;
        temp += data.TU2Level * data.TU2Power;
        temp *= TotalBoost();
        temp *= Pow(1.2, prestige.levels[1]);
        return temp;
    }

    private BigDouble TotalBoost()
    {
        var temp = prestige.TotalGemsBoost();
        temp *= events.eventTokenBoost;
        return temp;
    }

    public void Click()
    {
        data.count += TotalClickValue();
        data.totalcount += TotalClickValue();
    }

    public void BuyUpgr(string ID)
    {
        switch (ID)
        {
            case "CU1":
                {
                    if (data.count >= CU1NowCost)
                    {
                        data.count -= CU1NowCost;
                        data.CU1Level++;
                        data.ClickValue++;
                    }
                    break;
                }
            case "CU1Max":
                {
                    var cost = 20 * (Pow(1.2, data.CU1Level) * (Pow(1.2, data.CU1Max) - 1) / (1.2 - 1));
                    if (data.count >= CU1NowCost)
                    {
                        data.count -= cost;
                        data.CU1Level += (int)data.CU1Max;
                        data.ClickValue += data.CU1Max;
                    }
                    break;
                }
            case "TU1":
                {
                    if (data.count >= TU1NowCost)
                    {
                        data.count -= TU1NowCost;
                        data.TU1Level++;
                    }
                    break;
                }
            case "TU1Max":
                {
                    var cost = 50 * (Pow(1.2, data.TU1Level) * (Pow(1.2, data.TU1Max) - 1) / (1.2 - 1));
                    if (data.count >= TU1NowCost)
                    {
                        data.count -= cost;
                        data.TU1Level += (int)data.TU1Max;
                    }
                    break;
                }
            case "CU2":
                {
                    if (data.count >= CU2NowCost)
                    {
                        data.count -= CU2NowCost;
                        data.CU2Level++;
                        data.ClickValue += data.CU2Power;
                    }
                    break;
                }
            case "CU2Max":
                {
                    var cost = 150 * (Pow(1.5, data.CU2Level) * (Pow(1.5, data.CU2Max) - 1) / (1.5 - 1));
                    if (data.count >= CU2NowCost)
                    {
                        data.count -= cost;
                        data.CU2Level += (int)data.CU2Max;
                        data.ClickValue += (data.CU2Power * data.CU2Max);
                    }
                    break;
                }
            case "TU2":
                {
                    if (data.count >= TU2NowCost)
                    {
                        data.count -= TU2NowCost;
                        data.TU2Level++;
                    }
                    break;
                }
            case "TU2Max":
                {
                    var cost = 250 * (Pow(1.5, data.TU2Level) * (Pow(1.5, data.TU2Max) - 1) / (1.5 - 1));
                    if (data.count >= TU2NowCost)
                    {
                        data.count -= cost;
                        data.TU2Level += (int)data.TU2Max;
                    }
                    break;
                }
            default:
                Debug.Log("Something goes wrong with upgrades!");
                break;
        }
    }

    public void ChangTabs(string tab)
    {
        DisableAll();
        switch(tab)
        {
            case "GAME":
                GameMenuGroup.gameObject.SetActive(true);
                break;
            case "UPGRADE":
                UpgrMenuGroup.gameObject.SetActive(true);
                break;
            case "ACHIEVEMENT":
                AchievementsGroup.gameObject.SetActive(true);
                break;
            case "EVENT":
                EventGroup.gameObject.SetActive(true);
                break;
            case "BONUS":
                prestige.prestige.gameObject.SetActive(true);
                break;
        }

        void DisableAll()
        {
            GameMenuGroup.gameObject.SetActive(false);
            UpgrMenuGroup.gameObject.SetActive(false);
            AchievementsGroup.gameObject.SetActive(false);
            EventGroup.gameObject.SetActive(false);
            prestige.prestige.gameObject.SetActive(false);
        }
    }

    public void GoToSettings()
    {
        settings.gameObject.SetActive(true);
    }

    public void GoBackFromSettings()
    {
        settings.gameObject.SetActive(false);
    }

    public void Save()
    {
        SaveSystem.SavePlayer(data);
    }

    public void FullReset()
    {
        data.FullReset();

    }
}

public class Methods : MonoBehaviour
{
    public static void CanvasGroupChanger(bool x, CanvasGroup name)
    {
        name.alpha = x ? 1 : 0;
        name.interactable = x;
        name.blocksRaycasts = x;
    }

    public static void BigDoubleFill(BigDouble x, BigDouble y, Image fill)
    {
        float z;
        var a = x / y;
        if (a < 0.001)
            z = 0;
        else if (a > 10)
            z = 1;
        else
            z = (float)a.ToDouble();
        fill.fillAmount = z;
    }

    public static string NotationMethod(BigDouble numb, string freq)
    {
        if (numb > 1000)
        {
            var exponent = Floor(Log10(Abs(numb)));
            var mantissa = numb / Pow(10, exponent);
            return mantissa.ToString("F2") + "e" + exponent;
        }
        return numb.ToString(freq);
    }
}