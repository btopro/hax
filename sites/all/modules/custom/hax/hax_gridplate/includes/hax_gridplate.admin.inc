<?php

/**
 * @file
 * hax_gridplate editing UI.
 */

/**
 * UI controller.
 */
class HaxGridplateUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   *
   * Main reason for doing this is that parent class hook_menu() is, optimized
   * for entity type administration.
   */
  public function hook_menu() {
    // TODO: EntityDefaultUIController controller automatically adds the menu
    // to import entities, but there is a bug with this action and can not work
    // with the version of your entity_api module, track the issue # 2112755
    // https://www.drupal.org/node/2112755
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_object';

    $items = parent::hook_menu();

    // Change the overview menu type for the list of Hax Gridplate.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    // Replaces default entity title.
    $items[$this->path]['title'] = 'Hax Gridplate';

    // Extend the 'add' path.
    $items[$this->path . '/add'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType),
      'page callback' => 'entity_ui_bundle_add_page',
      'page arguments' => array($this->entityType),
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
    );

    $items[$this->path . '/add/%'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType, $this->id_count + 1),
      'page callback' => 'entity_ui_get_bundle_add_form',
      'page arguments' => array($this->entityType, $this->id_count + 1),
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
    );

    $items['hax_gridplate/' . $wildcard] = array(
      'title callback' => 'hax_gridplate_page_title',
      'title arguments' => array(1),
      'page callback' => 'hax_gridplate_page_view',
      'page arguments' => array(1),
      'access callback' => 'entity_access',
      'access arguments' => array('view', $this->entityType),
    );

    return $items;
  }
}

/**
 * Form callback: create or edit a Hax Gridplate.
 */
function hax_gridplate_form($form, &$form_state, $hax_gridplate, $op = 'edit', $entity_type) {
  // Add the breadcrumb for the form's location.
  hax_gridplate_set_breadcrumb();

  // Add the default field elements.
  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Hax Gridplate Label'),
    '#default_value' => isset($hax_gridplate->label) ? $hax_gridplate->label : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );

  // Add the field related form elements.
  $form_state['hax_gridplate'] = $hax_gridplate;
  field_attach_form('hax_gridplate', $hax_gridplate, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Hax Gridplate'),
    '#submit' => $submit + array('hax_gridplate_edit_form_submit'),
  );

  if (!empty($hax_gridplate->label)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete Hax Gridplate'),
      '#suffix' => l(t('Cancel'), 'admin/content/hax_gridplate'),
      '#submit' => $submit + array('hax_gridplate_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'] = array('hax_gridplate_edit_form_validate');

  return $form;
}

/**
 * Form API validate callback for the Hax Gridplate form.
 */
function hax_gridplate_edit_form_validate(&$form, &$form_state) {
  $hax_gridplate = $form_state['hax_gridplate'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('hax_gridplate', $hax_gridplate, $form, $form_state);
}

/**
 * Form API submit callback for the Hax Gridplate form.
 */
function hax_gridplate_edit_form_submit(&$form, &$form_state) {
  // Save the entity and go back to the list of Hax Gridplate.
  $hax_gridplate = entity_ui_controller('hax_gridplate')->entityFormSubmitBuildEntity($form, $form_state);

  // Add in created and changed times.
  $is_new_entity = $hax_gridplate->is_new = isset($hax_gridplate->is_new) ? $hax_gridplate->is_new : 0;
  if ($is_new_entity) {
    $hax_gridplate->created = time();
  }

  $hax_gridplate->changed = time();

  $hax_gridplate->save();

  // Send feedback message to the user.
  $message = t("Hax Gridplate :label updated.", array(':label' => $hax_gridplate->label));

  if ($is_new_entity) {
    $message = t("Hax Gridplate :label created.", array(':label' => $hax_gridplate->label));
  }

  drupal_set_message($message);

  $form_state['redirect'] = 'admin/content/hax_gridplate';
}

/**
 * Form API submit callback for the delete button.
 */
function hax_gridplate_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/hax_gridplate/manage/' . $form_state['hax_gridplate']->mjid . '/delete';
}

/**
 * Sets the breadcrumb for administrative Hax Gridplate pages.
 */
function hax_gridplate_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Hax Gridplate'), 'admin/content/hax_gridplate'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
