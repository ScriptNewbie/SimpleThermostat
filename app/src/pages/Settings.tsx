import {
  Container,
  FormControl,
  FormLabel,
  Heading,
  Input,
  Button,
  VStack,
  Spinner,
  Center,
} from "@chakra-ui/react";
import { useRef } from "react";
import { useSettings } from "../hooks/useSettings";
import { useMutateSettings } from "../hooks/useMutateSettings";
import { useData } from "../hooks/useData";

export const Settings = () => {
  const { data: settings, isSuccess } = useSettings();
  const { data } = useData();
  const { mutate, isPending } = useMutateSettings();

  const ssidRef = useRef<HTMLInputElement>(null);
  const wpaRef = useRef<HTMLInputElement>(null);
  const hysteresisRef = useRef<HTMLInputElement>(null);
  const defaultTemperatureRef = useRef<HTMLInputElement>(null);

  const handleSubmit = (event: React.FormEvent) => {
    event.preventDefault();

    if (!settings) return;

    const ssid = ssidRef.current?.value;
    const wpa = wpaRef.current?.value;
    const hysteresis = hysteresisRef.current?.value;
    const defaultTemperature = defaultTemperatureRef.current?.value;

    const updatedConfig = {
      ssid: ssid,
      wpa: wpa,
      hysteresis: hysteresis ? parseFloat(hysteresis) : undefined,
      defaultTemperature: defaultTemperature
        ? parseFloat(defaultTemperature)
        : undefined,
    };

    mutate(updatedConfig);
  };

  return (
    <Container>
      <Heading>Ustawienia</Heading>
      {isSuccess ? (
        <form onSubmit={handleSubmit}>
          <VStack align="stretch">
            <FormControl>
              <FormLabel>IP</FormLabel>
              <Input disabled value={data?.ip ?? ""} type="text" />
            </FormControl>
            <FormControl>
              <FormLabel>SSID</FormLabel>
              <Input defaultValue={settings.ssid} type="text" ref={ssidRef} />
            </FormControl>
            <FormControl>
              <FormLabel>WPA</FormLabel>
              <Input defaultValue={settings.wpa} type="password" ref={wpaRef} />
            </FormControl>
            <FormControl>
              <FormLabel>Histereza</FormLabel>
              <Input
                defaultValue={settings.hysteresis}
                type="number"
                ref={hysteresisRef}
              />
            </FormControl>
            <FormControl>
              <FormLabel>Domyślna temperatura</FormLabel>
              <Input
                defaultValue={settings.defaultTemperature}
                type="number"
                ref={defaultTemperatureRef}
              />
            </FormControl>
            <Button isLoading={isPending} type="submit">
              OK
            </Button>
          </VStack>
        </form>
      ) : (
        <Center>
          <Spinner mt={3} justifySelf="center" />
        </Center>
      )}
    </Container>
  );
};
