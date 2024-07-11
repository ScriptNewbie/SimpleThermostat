import { useState } from "react";
import { HeatingPeriod } from "../../hooks/useSettings";
import { Period } from "./Period";
import { Button, Flex } from "@chakra-ui/react";
import { useMutateSettings } from "../../hooks/useMutateSettings";

export const Periods = ({ periods }: { periods: HeatingPeriod[] }) => {
  const { mutate, isPending } = useMutateSettings();
  const [periodsState, setPeriodsState] = useState(
    periods.map((period, index) => ({ ...period, index }))
  );

  const [touched, setTouched] = useState(false);

  const updatePeriod = (
    index: number,
    start: string,
    end: string,
    temperature: number
  ) => {
    setPeriodsState((prev) =>
      prev.map((period) =>
        period.index === index ? { start, end, temperature, index } : period
      )
    );
    setTouched(true);
  };

  const addPeriod = () => {
    setPeriodsState((prev) => [
      ...prev,
      { start: "", end: "", temperature: 20, index: periodsState.length },
    ]);
  };

  const deletePeriod = (index: number) => {
    setPeriodsState((prev) => prev.filter((period) => period.index !== index));
    setTouched(true);
  };

  return (
    <Flex direction="column" m={0} gap={1}>
      {periodsState.map((period) => (
        <Period onDelete={deletePeriod} key={period.index} onChange={updatePeriod} period={period} />
      ))}
      <Flex mt={2} w="100%" justifyContent="space-between">
        <Button
          isLoading={isPending}
          onClick={() => {
            setTouched(false);
            const data = {
              heatingPeriods: periodsState
                .filter(({ start, end }) => start && end)
                .map(({ start, end, temperature }) => ({
                  start,
                  end,
                  temperature,
                })),
            };
            mutate(data);
          }}
          isDisabled={!touched}
        >
          Zapisz
        </Button>
        <Button isDisabled={isPending} onClick={addPeriod}>
          +
        </Button>
      </Flex>
    </Flex>
  );
};
