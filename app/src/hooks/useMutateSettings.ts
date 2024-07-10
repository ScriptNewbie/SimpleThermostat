import { useMutation } from "@tanstack/react-query";
import { Settings } from "./useSettings";
import axios from "axios";

export const useMutateSettings = () => {
  return useMutation({
    mutationFn: async (settings: Partial<Settings>) => {
      const { data } = await axios.post<Settings>(
        "http://192.168.120.200/settings",
        settings
      );
      return data;
    },
  });
};
