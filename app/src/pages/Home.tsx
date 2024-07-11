import {
  Center,
  Container,
  Heading,
  SimpleGrid,
  Spinner,
  Text,
} from "@chakra-ui/react";
import { useData } from "../hooks/useData";
import { useSettings } from "../hooks/useSettings";
import { Periods } from "./components/Periods";

export const Home = () => {
  const { data, isSuccess, isLoading } = useData();
  const {
    data: settings,
    isSuccess: settingsSuccess,
    isLoading: settingsIsLoading,
  } = useSettings();

  return (
    <Container>
      <Heading>Dom</Heading>
      {(isLoading || settingsIsLoading) && (
        <Center>
          <Spinner mt={3} justifySelf="center" />
        </Center>
      )}
      {isSuccess &&
        (() => {
          const { temperature, targetTemperature, time, heating } = data;
          return (
            <SimpleGrid mb={2} columns={2}>
              <Text>Godzina:</Text>
              <Text>{time}</Text>

              <Text>Temperatura: </Text>
              <Text color={temperature > targetTemperature ? "green" : "red"}>
                {temperature}°C
              </Text>
              <Text>Docelowa:</Text>
              <Text>{targetTemperature}°C</Text>
              <Text>Grzałka:</Text>
              <Text color={heating ? "green" : "red"}>
                {heating ? "Aktywna" : "Nieaktywna"}
              </Text>
            </SimpleGrid>
          );
        })()}
      {settingsSuccess && <Periods periods={settings.heatingPeriods} />}
    </Container>
  );
};
