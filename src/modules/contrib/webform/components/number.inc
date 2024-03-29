<?php

/**
 * @file
 * Webform module number component.
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_number() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'value' => '',
    'required' => 0,
    'extra' => array(
      'type' => 'textfield',
      'field_prefix' => '',
      'field_suffix' => '',
      'disabled' => 0,
      'unique' => 0,
      'title_display' => 0,
      'description' => '',
      'description_above' => FALSE,
      'placeholder' => '',
      'attributes' => array(),
      'private' => FALSE,
      'analysis' => FALSE,
      'min' => '',
      'max' => '',
      'step' => '',
      'decimals' => '',
      'point' => '.',
      'separator' => ',',
      'integer' => 0,
      'excludezero' => 0,
    ),
  );
}

/**
 * Implements _webform_theme_component().
 */
function _webform_theme_number() {
  return array(
    'webform_number' => array(
      'render element' => 'element',
      'file' => 'components/number.inc',
    ),
    'webform_display_number' => array(
      'render element' => 'element',
      'file' => 'components/number.inc',
    ),
  );
}

/**
 * Fix the view field(s) that are automatically generated for number components.
 */
function _webform_view_field_number($component, $fields) {
  foreach ($fields as &$field) {
    $field['webform_datatype'] = 'number';
  }
  return $fields;
}

/**
 * Implements _webform_edit_component().
 */
function _webform_edit_number($component) {
  $form = array();
  $form['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Default value'),
    '#default_value' => $component['value'],
    '#description' => t('The default value of the field.') . ' ' . theme('webform_token_help'),
    '#size' => 60,
    '#maxlength' => 1024,
    '#weight' => 0,
  );
  $form['display']['type'] = array(
    '#type' => 'radios',
    '#title' => t('Element type'),
    '#options' => array(
      'textfield' => t('Text field'),
      'select' => t('Select list'),
    ),
    '#default_value' => $component['extra']['type'],
    '#description' => t('A minimum and maximum value are required if displaying as a select.'),
    '#weight' => -1,
    '#parents' => array('extra', 'type'),
  );
  $form['display']['placeholder'] = array(
    '#type' => 'textfield',
    '#title' => t('Placeholder'),
    '#default_value' => $component['extra']['placeholder'],
    '#description' => t('The placeholder will be shown in the field until the user starts entering a value.'),
    '#weight' => 1,
    '#parents' => array('extra', 'placeholder'),
  );
  $form['display']['field_prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Prefix text placed to the left of the field'),
    '#default_value' => $component['extra']['field_prefix'],
    '#description' => t('Examples: $, #, -.'),
    '#size' => 20,
    '#maxlength' => 127,
    '#weight' => 1.1,
    '#parents' => array('extra', 'field_prefix'),
  );
  $form['display']['field_suffix'] = array(
    '#type' => 'textfield',
    '#title' => t('Postfix text placed to the right of the field'),
    '#default_value' => $component['extra']['field_suffix'],
    '#description' => t('Examples: lb, kg, %.'),
    '#size' => 20,
    '#maxlength' => 127,
    '#weight' => 1.2,
    '#parents' => array('extra', 'field_suffix'),
  );
  $form['display']['disabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disabled'),
    '#return_value' => 1,
    '#description' => t('Make this field non-editable. Useful for displaying default value. Changeable via JavaScript or developer tools.'),
    '#weight' => 11,
    '#default_value' => $component['extra']['disabled'],
    '#parents' => array('extra', 'disabled'),
  );
  $form['display']['decimals'] = array(
    '#type' => 'select',
    '#title' => t('Decimal places'),
    '#options' => array('' => t('Automatic')) + backdrop_map_assoc(range(0, 10)),
    '#description' => t('Automatic will display up to @count decimals places if needed. A value of "2" is common to format currency amounts.', array('@count' => '4')),
    '#default_value' => $component['extra']['decimals'],
    '#weight' => 2,
    '#parents' => array('extra', 'decimals'),
    '#element_validate' => array('_webform_edit_number_validate'),
  );
  $form['display']['separator'] = array(
    '#type' => 'select',
    '#title' => t('Thousands separator'),
    '#options' => array(
      ',' => t('Comma (,)'),
      '.' => t('Period (.)'),
      ' ' => t('Space ( )'),
      '' => t('None'),
    ),
    '#default_value' => $component['extra']['separator'],
    '#weight' => 3,
    '#parents' => array('extra', 'separator'),
    '#element_validate' => array('_webform_edit_number_validate'),
  );
  $form['display']['point'] = array(
    '#type' => 'select',
    '#title' => t('Decimal point'),
    '#options' => array(
      ',' => t('Comma (,)'),
      '.' => t('Period (.)'),
    ),
    '#default_value' => $component['extra']['point'],
    '#weight' => 4,
    '#parents' => array('extra', 'point'),
    '#element_validate' => array('_webform_edit_number_validate'),
  );
  $form['validation']['unique'] = array(
    '#type' => 'checkbox',
    '#title' => t('Unique'),
    '#return_value' => 1,
    '#description' => t('Check that all entered values for this field are unique. The same value is not allowed to be used twice.'),
    '#weight' => 1,
    '#default_value' => $component['extra']['unique'],
    '#parents' => array('extra', 'unique'),
  );
  $form['validation']['integer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Integer'),
    '#return_value' => 1,
    '#description' => t('Permit only integer values as input. For example, 12.34 would be invalid.'),
    '#weight' => 1.5,
    '#default_value' => $component['extra']['integer'],
    '#parents' => array('extra', 'integer'),
  );
  $form['validation']['min'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum'),
    '#default_value' => $component['extra']['min'],
    '#description' => t('Minimum numeric value. For example, 0 would ensure non-negative numbers.'),
    '#size' => 5,
    '#maxlength' => 10,
    '#weight' => 2.1,
    '#parents' => array('extra', 'min'),
    '#element_validate' => array('_webform_edit_number_validate'),
  );
  $form['validation']['max'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum'),
    '#default_value' => $component['extra']['max'],
    '#description' => t('Maximum numeric value. This may also determine the display width of your field.'),
    '#size' => 5,
    '#maxlength' => 10,
    '#weight' => 2.2,
    '#parents' => array('extra', 'max'),
    '#element_validate' => array('_webform_edit_number_validate'),
  );
  $form['validation']['step'] = array(
    '#type' => 'textfield',
    '#title' => t('Step'),
    '#default_value' => $component['extra']['step'],
    '#description' => t('Limit options to a specific increment. For example, a step of "5" would allow values 5, 10, 15, etc.'),
    '#size' => 5,
    '#maxlength' => 10,
    '#weight' => 3,
    '#parents' => array('extra', 'step'),
    '#element_validate' => array('_webform_edit_number_validate'),
  );
  // Analysis settings.
  $form['analysis'] = array(
    '#type' => 'fieldset',
    '#title' => t('Analysis'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => 10,
  );
  $form['analysis']['excludezero'] = array(
    '#type' => 'checkbox',
    '#title' => t('Exclude zero'),
    '#return_value' => 1,
    '#description' => t('Exclude entries of zero (or blank) when counting submissions to calculate average and standard deviation.'),
    '#weight' => 1.5,
    '#default_value' => $component['extra']['excludezero'],
    '#parents' => array('extra', 'excludezero'),
  );
  return $form;
}

/**
 * Theme function to render a number component.
 */
function theme_webform_number($variables) {
  $element = $variables['element'];

  // This IF statement is mostly in place to allow our tests to set type="text"
  // because SimpleTest does not support type="number".
  if (!isset($element['#attributes']['type'])) {
    // HTML5 number fields are no long used pending better browser support.
    // See issues #2290029, #2202905.
    // @code
    // $element['#attributes']['type'] = 'number';
    // @endcode
    $element['#attributes']['type'] = 'text';
  }

  // Step property *must* be a full number with 0 prefix if a decimal.
  if (!empty($element['#step']) && filter_var((float) $element['#step'], FILTER_VALIDATE_INT) === FALSE) {
    $decimals = strlen($element['#step']) - strrpos($element['#step'], '.') - 1;
    $element['#step'] = sprintf('%1.' . $decimals . 'F', $element['#step']);
  }

  // If the number is not an integer and step is undefined/empty, set the "any"
  // value to allow any decimal.
  if (empty($element['#integer']) && empty($element['#step'])) {
    $element['#step'] = 'any';
  }
  elseif ($element['#integer'] && empty($element['#step'])) {
    $element['#step'] = 1;
  }

  // Convert properties to attributes on the element if set.
  foreach (array('id', 'name', 'value', 'size', 'min', 'max', 'step') as $property) {
    if (isset($element['#' . $property]) && $element['#' . $property] !== '') {
      $element['#attributes'][$property] = $element['#' . $property];
    }
  }
  _form_set_class($element, array('form-text', 'form-number'));

  return '<input' . backdrop_attributes($element['#attributes']) . ' />';
}

/**
 * Implements _webform_render_component().
 */
function _webform_render_number($component, $value = NULL, $filter = TRUE, $submission = NULL) {
  $node = isset($component['nid']) ? node_load($component['nid']) : NULL;

  $element = array(
    '#title' => $filter ? webform_filter_xss($component['name']) : $component['name'],
    '#title_display' => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
    '#default_value' => $filter ? webform_replace_tokens($component['value'], $node) : $component['value'],
    '#required' => $component['required'],
    '#weight' => $component['weight'],
    '#field_prefix' => empty($component['extra']['field_prefix']) ? NULL : ($filter ? webform_filter_xss($component['extra']['field_prefix']) : $component['extra']['field_prefix']),
    '#field_suffix' => empty($component['extra']['field_suffix']) ? NULL : ($filter ? webform_filter_xss($component['extra']['field_suffix']) : $component['extra']['field_suffix']),
    '#description' => $filter ? webform_filter_descriptions($component['extra']['description'], $node) : $component['extra']['description'],
    '#attributes' => $component['extra']['attributes'],
    '#element_validate' => array('_webform_validate_number'),
    '#theme_wrappers' => array('webform_element'),
    '#min' => $component['extra']['min'],
    '#max' => $component['extra']['max'],
    '#step' => $component['extra']['step'] ? abs($component['extra']['step']) : '',
    '#integer' => $component['extra']['integer'],
    '#point' => $component['extra']['point'],
    '#separator' => $component['extra']['separator'],
    '#decimals' => $component['extra']['decimals'],
    '#translatable' => array('title', 'description', 'field_prefix', 'field_suffix', 'placeholder'),
  );

  if ($component['required']) {
    $element['#attributes']['required'] = 'required';
  }

  if ($component['extra']['placeholder']) {
    $element['#attributes']['placeholder'] = $component['extra']['placeholder'];
  }

  // Set the decimal count to zero for integers.
  if ($element['#integer'] && $element['#decimals'] === '') {
    $element['#decimals'] = 0;
  }

  // Flip the min and max properties to make min less than max if needed.
  if ($element['#min'] !== '' && $element['#max'] !== '' && $element['#min'] > $element['#max']) {
    $max = $element['#min'];
    $element['#min'] = $element['#max'];
    $element['#max'] = $max;
  }

  // Ensure #step starts with a zero if a decimal.
  if (filter_var((float) $element['#step'], FILTER_VALIDATE_INT) === FALSE) {
    $decimals = strlen($element['#step']) - strrpos($element['#step'], '.') - 1;
    $element['#step'] = sprintf('%1.' . $decimals . 'F', $element['#step']);
  }

  if ($component['extra']['type'] == 'textfield') {
    // Render as textfield.
    $element['#type'] = 'webform_number';

    // Set the size property based on #max, to ensure consistent behavior for
    // browsers that do not support type = number.
    if ($element['#max']) {
      $element['#size'] = strlen($element['#max']) + 1;
    }
  }
  else {
    // Render as select.
    $element['#type'] = 'select';

    // Create user-specified options list as an array.
    $element['#options'] = _webform_number_select_options($component);

    // Add default options if using a select list with no default. This trigger's
    // Backdrop's adding of the option for us. See form_process_select().
    if ($component['extra']['type'] == 'select' && $element['#default_value'] === '') {
      $element['#empty_value'] = '';
    }
  }

  // Set user-entered values.
  if (isset($value[0])) {
    // If the value has been standardized, convert it to the expected format
    // for display to the user.
    if (webform_number_format_match($value[0], '.', '')) {
      $element['#default_value'] = _webform_number_format($component, $value[0]);
    }
    // Otherwise use the user-defined input.
    else {
      $element['#default_value'] = $value[0];
    }
  }

  // Enforce uniqueness.
  if ($component['extra']['unique']) {
    $element['#element_validate'][] = 'webform_validate_unique';
  }

  // Set readonly if disabled.
  if ($component['extra']['disabled']) {
    if ($filter) {
      $element['#attributes']['readonly'] = 'readonly';
    }
    else {
      $element['#disabled'] = TRUE;
    }
  }

  return $element;
}

/**
 * Implements _webform_display_component().
 */
function _webform_display_number($component, $value, $format = 'html', $submission = array()) {
  $empty = !isset($value[0]) || $value[0] === '';
  return array(
    '#title' => $component['name'],
    '#title_display' => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
    '#weight' => $component['weight'],
    '#theme' => 'webform_display_number',
    '#theme_wrappers' => $format == 'html' ? array('webform_element') : array('webform_element_text'),
    '#field_prefix' => $empty ? '' : $component['extra']['field_prefix'],
    '#field_suffix' => $empty ? '' : $component['extra']['field_suffix'],
    '#format' => $format,
    '#value' => $empty ? '' : _webform_number_format($component, $value[0]),
    '#translatable' => array('title', 'placeholder'),
  );
}

/**
 * Format the output of data for this component.
 */
function theme_webform_display_number($variables) {
  $element = $variables['element'];
  $prefix = $element['#format'] == 'html' ? '' : $element['#field_prefix'];
  $suffix = $element['#format'] == 'html' ? '' : $element['#field_suffix'];
  $value = $element['#format'] == 'html' ? check_plain($element['#value']) : $element['#value'];
  return $value !== '' ? ($prefix . $value . $suffix) : ' ';
}

/**
 * Implements _webform_analysis_component().
 */
function _webform_analysis_number($component, $sids = array(), $single = FALSE, $join = NULL) {
  $advanced_stats = $single;

  $query = db_select('webform_submitted_data', 'wsd', array('fetch' => PDO::FETCH_ASSOC))
    ->fields('wsd', array('data'))
    ->condition('wsd.nid', $component['nid'])
    ->condition('wsd.cid', $component['cid']);

  if (count($sids)) {
    $query->condition('wsd.sid', $sids, 'IN');
  }

  if ($join) {
    $query->innerJoin($join, 'ws2_', 'wsd.sid = ws2_.sid');
  }

  $population = array();
  $submissions = 0;
  $non_zero = 0;
  $non_empty = 0;
  $sum = 0;

  $result = $query->execute();
  foreach ($result as $data) {
    $value = trim($data['data']);
    $number = (float) $value;
    $non_empty += (integer) ($value !== '');
    $non_zero += (integer) ($number != 0.0);
    $sum += $number;
    $population[] = $number;
    $submissions++;
  }
  sort($population, SORT_NUMERIC);

  // Average and population count.
  if ($component['extra']['excludezero']) {
    $average = $non_zero ? ($sum / $non_zero) : 0;
    $average_title = t('Average !mu excluding zeros/blanks', array('!mu' => $advanced_stats ? '(&mu;)' : ''));
    // Sample (sub-set of total population).
    $population_count = $non_zero - 1;
    $sigma = 'sd';
    $description = t('sample');
  }
  else {
    $average = $submissions ? ($sum / $submissions) : 0;
    $average_title = t('Average !mu including zeros/blanks', array('!mu' => $advanced_stats ? '(&mu;)' : ''));
    // Population.
    $population_count = $submissions;
    $sigma = '&sigma;';
    $description = t('population');
  }

  // Formatting.
  $average = _webform_number_format($component, $average);
  $sum = _webform_number_format($component, $sum);

  $rows[] = array(t('Zero/blank'), ($submissions - $non_zero));
  $rows[] = array(t('User entered value'), $non_empty);

  $other[] = array(t('Sum') . ($advanced_stats ? ' (&Sigma;)' : ''), $sum);
  $other[] = array($average_title, $average);

  if (!$advanced_stats && $sum != 0) {
    $other[] = l(t('More stats »'), 'node/' . $component['nid'] . '/webform-results/analysis/' . $component['cid']);
  }

  // Normal distribution information.
  if ($advanced_stats && $population_count && $sum != 0) {
    // Standard deviation.
    $stddev = 0;
    foreach ($population as $value) {
      // Obtain the total of squared variances.
      $stddev += pow(($value - $average), 2);
    }
    if ($population_count > 0) {
      $stddev = sqrt($stddev / $population_count);
    }
    else {
      $stddev = sqrt($stddev);
    }

    // Skip the rest of the distribution rows if standard deviation is 0.
    if (empty($stddev)) {
      return array(
        'table_rows' => $rows,
        'other_data' => $other,
      );
    }

    // Build normal distribution table rows.
    $count = array();
    $percent = array();
    $limit = array();
    $index = 0;

    $count[] = 0;
    $limit[] = $average - ($stddev * 4);
    foreach ($population as $value) {
      while ($value >= $limit[$index]) {
        $percent[] = number_format($count[$index] / $population_count * 100, 2, '.', '');
        $limit[] = $limit[$index] + $stddev;
        $index += 1;
        if ($limit[$index] == $average) {
          $limit[$index] = $limit[$index] + $stddev;
        }
        $count[$index] = 0;
      }
      $count[$index] += 1;
    }
    $percent[] = number_format($count[$index] / $population_count * 100, 2, '.', '');

    // Format normal distribution table output.
    $stddev = _webform_number_format($component, $stddev);
    $low = _webform_number_format($component, $population[0]);
    $high = _webform_number_format($component, end($population));
    foreach ($limit as $key => $value) {
      $limit[$key] = _webform_number_format($component, $value);
    }

    // Column headings (override potential theme uppercase, for example, Seven in D7).
    $header = array(
      t('Normal Distribution'),
      array('data' => '-4' . $sigma, 'style' => 'text-transform: lowercase;'),
      array('data' => '-3' . $sigma, 'style' => 'text-transform: lowercase;'),
      array('data' => '-2' . $sigma, 'style' => 'text-transform: lowercase;'),
      array('data' => '-1' . $sigma, 'style' => 'text-transform: lowercase;'),
      array('data' => '+1' . $sigma, 'style' => 'text-transform: lowercase;'),
      array('data' => '+2' . $sigma, 'style' => 'text-transform: lowercase;'),
      array('data' => '+3' . $sigma, 'style' => 'text-transform: lowercase;'),
      array('data' => '+4' . $sigma, 'style' => 'text-transform: lowercase;'),
    );

    // Insert row labels.
    array_unshift($limit, t('Boundary'));
    array_unshift($count, t('Count'));
    array_unshift($percent, t('% of !description', array('!description' => $description)));

    $normal_distribution = theme('table', array('header' => $header, 'rows' => array($limit, $count, $percent), 'sticky' => FALSE));

    $other[] = array(t('Range'), t('!low to !high', array('!low' => $low, '!high' => $high)));
    $other[] = array(t('Standard deviation (!sigma)', array('!sigma' => $sigma)), $stddev);
    $other[] = $normal_distribution;
  }

  return array(
    'table_rows' => $rows,
    'other_data' => $other,
  );
}

/**
 * Implements _webform_table_component().
 */
function _webform_table_number($component, $value) {
  return isset($value[0]) ? _webform_number_format($component, $value[0]) : '';
}

/**
 * Implements _webform_action_set_component().
 */
function _webform_action_set_number($component, &$element, &$form_state, $value) {
  $element['#value'] = $value;
  form_set_value($element, $value, $form_state);
}

/**
 * Implements _webform_csv_headers_component().
 */
function _webform_csv_headers_number($component, $export_options) {
  $header = array();
  $header[0] = '';
  $header[1] = '';
  $header[2] = $export_options['header_keys'] ? $component['form_key'] : $component['name'];
  return $header;
}

/**
 * Implements _webform_csv_data_component().
 */
function _webform_csv_data_number($component, $export_options, $value) {
  if (isset($value[0]) && is_numeric($value[0]) && $component['extra']['decimals'] !== '') {
    $value[0] = number_format($value[0], $component['extra']['decimals'], '.', '');
  }
  return isset($value[0]) ? $value[0] : '';
}

/**
 * A Backdrop Form API Validation function.
 *
 * Validates the entered values from number components on the client-side form.
 *
 * @param array $element
 *   The form element. May either be a select or a webform_number element.
 * @param array $form_state
 *   The full form state for the webform.
 */
function _webform_validate_number($element, &$form_state) {
  // Trim spaces for basic cleanup.
  $value = trim($element['#value']);
  form_set_value($element, $value, $form_state);

  if ($value != '') {
    // First check that the entered value matches the expected value.
    if (!webform_number_format_match($value, $element['#point'], $element['#separator'])) {
      form_error($element, t('!name field value must format numbers as "@example".', array('!name' => $element['#title'], '@example' => webform_number_format(12345.6789, $element['#decimals'], $element['#point'], $element['#separator']))));
      return;
    }

    // Numeric test.
    $numeric_value = webform_number_standardize($value, $element['#point']);
    if (is_numeric($numeric_value)) {
      // Range test.
      if ($element['#min'] != '' && $element['#max'] != '') {
        // Flip minimum and maximum if needed.
        if ($element['#max'] > $element['#min']) {
          $min = $element['#min'];
          $max = $element['#max'];
        }
        else {
          $min = $element['#max'];
          $max = $element['#min'];
        }
        if ($numeric_value > $max || $numeric_value < $min) {
          form_error($element, t('!name field value of @value should be in the range @min to @max.', array('!name' => $element['#title'], '@value' => $value, '@min' => $element['#min'], '@max' => $element['#max'])));
        }
      }
      elseif ($element['#max'] != '' && $numeric_value > $element['#max']) {
        form_error($element, t('!name field value must be less than or equal to @max.', array('!name' => $element['#title'], '@max' => $element['#max'])));
      }
      elseif ($element['#min'] != '' && $numeric_value < $element['#min']) {
        form_error($element, t('!name field value must be greater than or equal to @min.', array('!name' => $element['#title'], '@min' => $element['#min'])));
      }

      // Integer test.
      if ($element['#integer'] && filter_var((float) $numeric_value, FILTER_VALIDATE_INT) === FALSE) {
        form_error($element, t('!name field value of @value must be an integer.', array('!name' => $element['#title'], '@value' => $value)));
      }

      // Step test.
      $starting_number = $element['#min'] ? $element['#min'] : 0;
      if ($element['#step'] != 0 && webform_modulo($numeric_value - $starting_number, $element['#step']) != 0.0) {
        $samples = array(
          $starting_number,
          $starting_number + ($element['#step'] * 1),
          $starting_number + ($element['#step'] * 2),
          $starting_number + ($element['#step'] * 3),
        );
        if ($starting_number) {
          form_error($element, t('!name field value must be @start plus a multiple of @step. i.e. @samples, etc.', array('!name' => $element['#title'], '@start' => $element['#min'], '@step' => $element['#step'], '@samples' => implode(', ', $samples))));
        }
        else {
          form_error($element, t('!name field value must be a multiple of @step. i.e. @samples, etc.', array('!name' => $element['#title'], '@step' => $element['#step'], '@samples' => implode(', ', $samples))));
        }
      }
    }
    else {
      form_error($element, t('!name field value of @value must be numeric.', array('!name' => $element['#title'], '@value' => $value)));
    }
  }
}

/**
 * Implements _webform_submit_component().
 */
function _webform_submit_number($component, $value) {
  // Because _webform_validate_number() ensures the format matches when moving
  // forward through a form, this should always pass before saving into the
  // database. When moving backwards in a form, do not adjust the value, since
  // it has not yet been validated.
  if (webform_number_format_match($value, $component['extra']['point'], $component['extra']['separator'])) {
    $value = webform_number_standardize($value, $component['extra']['point']);
  }
  return $value;
}

/**
 * Validation of number edit form items.
 */
function _webform_edit_number_validate($element, &$form_state) {
  // Find the value of all related fields to this element.
  $parents = $element['#parents'];
  $key = array_pop($parents);
  $values = $form_state['values'];
  foreach ($parents as $parent) {
    $values = $values[$parent];
  }

  switch ($key) {
    case 'min':
      if ($values['min'] == '') {
        if (isset($values['type']) && $values['type'] === 'select') {
          form_error($element, t('Minimum is required when using a select list element.'));
        }
      }
      else {
        if (!is_numeric($values['min'])) {
          form_error($element, t('Minimum must be numeric.'));
        }
        if ($values['integer'] && filter_var((float) $values['min'], FILTER_VALIDATE_INT) === FALSE) {
          form_error($element, t('Minimum must have an integer value.'));
        }
      }
      break;

    case 'max':
      if ($values['max'] == '') {
        if (isset($values['type']) && $values['type'] === 'select') {
          form_error($element, t('Maximum is required when using a select list element.'));
        }
      }
      else {
        if (!is_numeric($values['max'])) {
          form_error($element, t('Maximum must be numeric.'));
        }
        if ($values['integer'] && filter_var((float) $values['max'], FILTER_VALIDATE_INT) === FALSE) {
          form_error($element, t('Maximum must have an integer value.'));
        }
      }
      break;

    case 'step':
      if ($values['step'] !== '') {
        if (!is_numeric($values['step'])) {
          form_error($element, t('Step must be numeric.'));
        }
        else {
          if ($values['integer'] && filter_var((float) $values['step'], FILTER_VALIDATE_INT) === FALSE) {
            form_error($element, t('Step must have an integer value.'));
          }
        }
      }
      break;
  }
  return TRUE;
}

/**
 * Generate select list options.
 */
function _webform_number_select_options($component) {
  $options = array();
  $step = abs($component['extra']['step']);

  // Step is optional and defaults to 1.
  $step = empty($step) ? 1 : $step;

  // Generate list in correct direction.
  $min = $component['extra']['min'];
  $max = $component['extra']['max'];
  $flipped = FALSE;
  if ($max < $min) {
    $min = $component['extra']['max'];
    $max = $component['extra']['min'];
    $flipped = TRUE;
  }

  for ($f = $min; $f <= $max; $f += $step) {
    $options[$f . ''] = $f . '';
  }

  // @todo HTML5 browsers apparently do not include the max value if it does
  // not line up with step. Restore this if needed in the future.
  // Add end limit if it's been skipped due to step.
  // @code
  // if (end($options) != $max) {
  //   $options[$f] = $max;
  // }
  // @endcode
  if ($flipped) {
    $options = array_reverse($options, TRUE);
  }

  // Apply requisite number formatting.
  foreach ($options as $key => $value) {
    $options[$key] = _webform_number_format($component, $value);
  }

  return $options;
}

/**
 * Apply number format based on a component and number value.
 */
function _webform_number_format($component, $value) {
  return webform_number_format($value, $component['extra']['decimals'], $component['extra']['point'], $component['extra']['separator']);
}

/**
 * Validates if a provided number string matches an expected format.
 *
 * This function allows the thousands separator to be optional, but decimal
 * points must be in the right location.
 *
 * A valid number is:
 *   1. optional minus sign.
 *   2. optional space.
 *   3. the rest of the string can't be just a decimal or blank.
 *   4. optional integer portion, with thousands separators.
 *   5. optional decimal portion, starting is a decimal separator.
 * Don't use preg_quote because a space is a valid thousands separator and
 * needs quoting for the 'x' option to preg_match.
 *
 * Based on http://stackoverflow.com/questions/5917082/regular-expression-to-match-numbers-with-or-without-commas-and-decimals-in-text.
 */
function webform_number_format_match($value, $point, $separator) {
  $thousands = $separator ? "\\$separator?" : '';
  $decimal = "\\$point";
  return preg_match("/
                    ^               # Start of string
                    -?              # Optional minus sign
                    \ ?             # Optional space
                    (?!\.?$)        # Assert looking ahead, not just a decimal or nothing
                      (?:           # Interger portion (non-grouping)
                        \d{1,3}     #   1 to 3 digits
                        (?:         #   Thousands group(s)
                        $thousands  #     Optional thousands separator
                        \d{2,3}     #     2 or 3 digits. Some countries use groups of 2 sometimes
                      )*            #   0 or more of these thousands groups
                    )?              # End of optional integer portion
                    (?:             # Decimal portion (non-grouping)
                      $decimal      #   Decimal point
                      \d*           #   0 or more digits
                    )?              # End of optional decimal portion
                    $
                    /x", $value);
}

/**
 * Format a number with thousands separator, decimal point, and decimal places.
 *
 * This function is a wrapper around PHP's native number_format(), but allows
 * the decimal places parameter to be NULL or an empty string, resulting in a
 * behavior of no change to the decimal places.
 */
function webform_number_format($value, $decimals = NULL, $point = '.', $separator = ',') {
  if (!is_numeric($value)) {
    return '';
  }

  // If no decimal places are specified, do a best guess length of decimals.
  if (is_null($decimals) || $decimals === '') {
    // If it's an integer, no decimals needed.
    if (filter_var((float) $value, FILTER_VALIDATE_INT) !== FALSE) {
      $decimals = 0;
    }
    else {
      $decimals = strlen($value) - strrpos($value, '.') - 1;
    }
    if ($decimals > 4) {
      $decimals = 4;
    }
  }

  return number_format($value, $decimals, $point, $separator);
}

/**
 * Given a number, convert it to string compatible with a PHP float.
 *
 * @param string $value
 *   The string value to be standardized into a numeric string.
 * @param string $point
 *   The point separator between the whole number and the decimals.
 *
 * @return string
 *   The converted number.
 */
function webform_number_standardize($value, $point) {
  // For simplicity, strip everything that's not the decimal point.
  $value = preg_replace('/[^\-0-9' . preg_quote($point, '/') . ']/', '', $value);
  // Convert the decimal point to a period.
  $value = str_replace($point, '.', $value);
  return $value;
}

/**
 * Custom modulo function that properly handles float division.
 *
 * See https://drupal.org/node/1601968.
 */
function webform_modulo($a, $b) {
  // Ensure values are either int or float.
  if (!is_numeric($a) || !is_numeric($b)) {
    return 0.0;
  }
  $a = +$a;
  $b = +$b;

  $modulo = $a - $b * (($b < 0) ? ceil($a / $b) : floor($a / $b));
  if (webform_compare_floats($modulo, 0.0) == 0 || webform_compare_floats($modulo, $b) == 0) {
    $modulo = 0.0;
  }
  return $modulo;
}

/**
 * Compare two floats.
 *
 * See @link http://php.net/manual/en/language.types.float.php @endlink.
 *
 * Comparison of floating point numbers for equality is surprisingly difficult,
 * as evidenced by the references below. The simple test in this function works
 * for numbers that are relatively close to 1E1. For very small numbers, it will
 * show false equality. For very large numbers, it will show false inequality.
 * Better implementations are hidered by the absense of PHP platform-specific
 * floating point constants to properly set the minimum absolute and relative
 * error in PHP.
 *
 * The use case for webform conditionals excludes very small or very large
 * numeric comparisons.
 *
 * See @link http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm @endlink
 * See @link http://floating-point-gui.de/errors/comparison/ @endlink
 * See @link http://en.wikipedia.org/wiki/IEEE_754-1985#Denormalized_numbers @endlink
 *
 * @param float $number_1
 *   The first number.
 * @param float $number_2
 *   The second number.
 *
 * @return int|null
 *   < 0 if number_1 is less than number_2; > 0 if number_1 is greater than
 *   number_2, 0 if they are equal, and NULL if either is not numeric.
 */
function webform_compare_floats($number_1, $number_2) {
  if (!is_numeric($number_1) || !is_numeric($number_2)) {
    return NULL;
  }

  $number_1 = (float) $number_1;
  $number_2 = (float) $number_2;

  $epsilon = 0.000001;
  if (abs($number_1 - $number_2) < $epsilon) {
    return 0;
  }
  elseif ($number_1 > $number_2) {
    return 1;
  }
  else {
    return -1;
  }
}
