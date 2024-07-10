import { useQuery } from "@tanstack/react-query";
import axios from "axios";

export interface HeatingPeriod {
  start: string;
  end: string;
  temperature: number;
}

export interface Settings {
  ssid: string;
  wpa: string;
  hysteresis: number;
  defaultTemperature: number;
  heatingPeriods: HeatingPeriod[];
}

export const useSettings = () => {
  return useQuery({
    queryKey: ["settings"],
    queryFn: async () => {
      const { data } = await axios.get<Settings>(
        "http://192.168.120.200/settings"
      );
      return data;
    },
  });
};
