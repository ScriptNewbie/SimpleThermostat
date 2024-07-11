import { useMutation, useQueryClient } from "@tanstack/react-query";
import { Settings } from "./useSettings";
import axios from "axios";

export const useMutateSettings = () => {
  const client = useQueryClient();
  return useMutation({
    mutationFn: async (settings: Partial<Settings>) => {
      const { data } = await axios.post<Settings>(
        "http://192.168.120.200/settings",
        settings
      );
      return data;
    },
    onSettled: () => {
      client.invalidateQueries({ queryKey: ["settings"] });
    },
  });
};
