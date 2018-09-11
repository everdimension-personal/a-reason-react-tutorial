let component = ReasonReact.statelessComponent("TodoItem");

let make = _children => {
  ...component,
  render: _self => <p> {ReasonReact.stringToElement("todo item")} </p>,
};
