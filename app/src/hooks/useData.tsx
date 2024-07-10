import { useQuery } from "@tanstack/react-query";
import axios from "axios";

export interface DeviceStatus {
  ip: string;
  temperature: number;
  time: string;
  heating: boolean;
  targetTemperature: number;
}

export const useData = () => {
  return useQuery({
    queryKey: ["data"],
    queryFn: async () => {
      const { data } = await axios.get<DeviceStatus>(
        "http://192.168.120.200/data"
      );
      return data;
    },
    refetchInterval: 2000,
  });
};
