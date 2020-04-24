package com.example.sidsapp;

public class IAQProcessor
{
    public enum EIAQLevel
    {
        EIAQLevel_Hazardous,
        EIAQLevel_VeryUnhealthy,
        EIAQLevel_Unhealthy,
        EIAQLevel_Moderate,
        EIAQLevel_Good,
        EIAQLevel_Great;
    }

    public static EIAQLevel calculateIAQ(double humidity, double co2)
    {
        double humScore, gasScore;
        double gasReference = co2*1000.0;
        double humReference = 40;

        // Humidity contribution
        if (humidity >= 38 && humidity <=42)
        {
            humScore = 0.25 * 100;
        } else {
            if (humidity < 38)
            {
                humScore = 0.25/humReference * humidity * 100;
            } else
            {
                humScore = ((-0.25/(100-humReference)*humidity) + 0.416666) * 100;
            }
        }

        // Gas contribution
        double gasLowerLimit = 500;
        double gasUpperLimit = 15000;

        if(gasReference > gasUpperLimit) gasReference = gasUpperLimit;
        if(gasReference < gasLowerLimit) gasReference = gasLowerLimit;

        gasScore = (0.75/(gasUpperLimit - gasLowerLimit)* gasReference -
                (gasLowerLimit*(0.75/(gasUpperLimit-gasLowerLimit))))*100;

        double airQualityScore = humScore + gasScore;

        double score = (100-airQualityScore)*5;

        if (score >= 301) return EIAQLevel.EIAQLevel_Hazardous; // hazardous
        else if (score >= 251 && score <= 300) return EIAQLevel.EIAQLevel_VeryUnhealthy; // Very unhealthy
        else if (score >= 201 && score <= 250 ) return EIAQLevel.EIAQLevel_Unhealthy; // Unhealthy
        else if (score >= 151 && score <= 200) return EIAQLevel.EIAQLevel_Moderate; // Moderate
        else if (score >=  51 && score <= 150) return EIAQLevel.EIAQLevel_Good; // Good
        else if (score <= 50) return EIAQLevel.EIAQLevel_Great; // Great

        return EIAQLevel.EIAQLevel_Great; // Great
    }
}
